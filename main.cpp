#include <iostream>
#include <regex>
#include <cstring>
#include <iomanip>
using namespace std;

bool buscarArchivo(char numeroVenta[100], FILE *);
bool existeNumero(char arrf[][20], char buscar[20], int tam);

int main() 
{
    char opcion;
    FILE *encabezadoVentas, *detalle_venta;
    char numeroVenta[100], numeroVenta2[100], nombre[80], nombre2[80], fecha[50], descripcion[100], continuar, claveArticulo[20],claveArticulo2[20];
    int claveCliente, consecutivo = 1, cantidad;
    char vistos[150][20],otroArticulo;
    float precio, total = 0;
    bool encontrado = false;
    regex patronVenta("^V\\d{2}-[1-9]$");
    regex patronNombre("^[a-zA-Z0-9 ]+$");
    regex patronFecha("^(0[1-9]|1[0-9]|2[0-9]|30|31)/(0[1-9]|1[0-2])/\\d{4}$");
    regex patronArticulo("^([1-9][0-9]?|100)$");

    cout << "a. Registro de Ventas" << endl;
    cout << "b. Total por articulo" << endl;
    cout << "c. Detalle por cliente" << endl;
    cout << "d. Salir" << endl;
    cin >> opcion;
    while(opcion!='d')
    {


    switch (opcion) 
    {
        case 'a':
            do {


            try 
            {
                encabezadoVentas = fopen("encabezado_venta.txt", "a+");
                detalle_venta = fopen("detalle_venta.txt", "a+");
                if (detalle_venta == NULL || encabezadoVentas == NULL) 
                {
                    throw "Error al crear el archivo";
                }
                else 
                {
                    do 
                    {
                        cout << "Ingresa el numero de venta" << endl;
                        cin >> numeroVenta;
                    }
                    while (!regex_match(numeroVenta, patronVenta) || buscarArchivo(numeroVenta, encabezadoVentas));

                    do 
                    {
                        cout << "Ingrese la clave del cliente" << endl;
                        cin >> claveCliente;
                        if (claveCliente < 100 || claveCliente > 200) 
                        {
                            cout << "Clave invalida, debe estar entre 100 y 200" << endl;
                        }
                    }
                    while (claveCliente < 100 || claveCliente > 200);
                    do {
                        cout << "Ingrese el nombre" << endl;
                        cin.ignore();
                        cin.getline(nombre, sizeof(nombre));

                    }while(!regex_match(nombre,patronNombre));

                    do {
                        cout << "Ingrese la fecha" << endl;
                        cin.getline(fecha, sizeof(fecha));
                    }while(!regex_match(fecha,patronFecha));

                    if (cin.fail()) 
                    {
                        throw "Se han ingresado datos invalidos";
                    }
                    fprintf(encabezadoVentas, "%s %d |%s| %s\n", numeroVenta, claveCliente, nombre, fecha);

                    do 
                    {
                        do 
                        {
                            cout << "Ingrese la clave del articulo" << endl;
                            cin >> claveArticulo;
                        }
                        while (existeNumero(vistos, claveArticulo, consecutivo) || !regex_match(claveArticulo, patronArticulo));

                        cout << "Ingrese la descripcion" << endl;
                        cin.ignore();
                        cin.getline(descripcion, sizeof(descripcion));

                        do 
                        {
                            cout << "Ingrese la cantidad deseada" << endl;
                            cin >> cantidad;
                        }
                        while (cantidad < 0);

                        do 
                        {
                            cout << "Ingrese el precio del articulo" << endl;
                            cin >> precio;
                        }
                        while (precio < 0);
                        strcpy(vistos[consecutivo], claveArticulo);

                        fprintf(detalle_venta, "%s %d %s |%s| %d %f\n", numeroVenta, consecutivo, claveArticulo, descripcion, cantidad, precio);
                        consecutivo++;

                        cout << "Desea continuar? S:si N:no";
                        cin >> continuar;
                    }
                    while (continuar != 'N');
                }
            }

            catch (const char *e) 
            {
                cout << e;
            }
            cout<<"Desea agregar otro articulo?"<<endl;
            cin>>otroArticulo;
            }while(otroArticulo!='s');

            fclose(encabezadoVentas);
            fclose(detalle_venta);
            break;

        case 'b':
            encabezadoVentas = fopen("encabezado_venta.txt", "r");
            detalle_venta = fopen("detalle_venta.txt", "r");
            if (detalle_venta == NULL || encabezadoVentas == NULL)
            {
                printf("No existen datos");
            }
            else
            {
                do {
                    cout<<"Ingrese la clave del articulo"<<endl;
                    cin>>claveArticulo2;
                }while(!regex_match(claveArticulo2,patronArticulo) );

                cout << left << setw(20) << "Descripcion"<< setw(15) << "Fecha"<< setw(20) << "Numero de venta"<< setw(15) << "Clave cliente"<< setw(20) << "Nombre cliente"<< setw(10) << "Cantidad"<< setw(10) << "Precio"<< setw(10) << "Subtotal" << endl;
                try {


                while (fscanf(detalle_venta, "%s %d %s |%[^|]| %d %f", numeroVenta, &consecutivo, claveArticulo, descripcion, &cantidad, &precio) == 6)
                {

                    if (strcmp(claveArticulo, claveArticulo2) == 0)
                    {
                        rewind(encabezadoVentas);

                        while (fscanf(encabezadoVentas, "%s %d |%[^|]| %s", numeroVenta2, &claveCliente, nombre, fecha) == 4 &&!encontrado )
                        {

                            if(strcmp(numeroVenta,numeroVenta2)==0) {
                                encontrado=true;
                                cout << left << setw(20) << descripcion
                               << setw(15) << fecha
                               << setw(20) << numeroVenta
                               << setw(15) << claveCliente
                               << setw(20) << nombre
                               << setw(10) << cantidad
                               << setw(10) << fixed << setprecision(2) << precio;
                                if (cantidad > 1e6 || precio > 1e6) {
                                    throw "El cálculo del subtotal puede causar desbordamiento.";
                                }
                                total+=cantidad * precio;
                               cout<< setw(10) << fixed << setprecision(2) << (cantidad * precio) << endl;
                            }

                        }
                        if(!encontrado) {
                            throw "No se encontro los datos en la cabezera";
                        }



                    }
                }
                    cout<<"El total es de: "<<total;
                }catch(const char *e) {
                    cout<<e;
                }


            }

            break;

        case 'c':
            try
            {


            encabezadoVentas = fopen("encabezado_venta.txt", "r");
            detalle_venta = fopen("detalle_venta.txt", "r");
            if (detalle_venta == NULL || encabezadoVentas == NULL)
            {
                printf("No existen datos");
            }
            else 
            {
                do 
                {
                    cout << "Ingrese el nombre del usuario" << endl;
                    cin.ignore();
                    cin.getline(nombre2, sizeof(nombre2));
                    if (!regex_match(nombre2, patronNombre)) 
                    {
                        printf("El nombre indicado no es valido\n");
                    }
                }
                while (!regex_match(nombre2, patronNombre));


                while (fscanf(encabezadoVentas, "%s %d |%[^|]| %s", numeroVenta2, &claveCliente, nombre, fecha) == 4 && !encontrado)
                {
                    if (strcmp(nombre, nombre2) == 0)
                    {

                        encontrado = true;

                        rewind(detalle_venta);
                        while (fscanf(detalle_venta, "%s %d %s |%[^|]| %d %f", numeroVenta, &consecutivo, claveArticulo, descripcion, &cantidad, &precio) == 6)
                        {
                            if (strcmp(numeroVenta, numeroVenta2) == 0)
                            {

                                total+=precio*cantidad;
                            }
                        }



                    }
                }

                if (!encontrado)
                {
                    throw "No se encontro ningun resgitro con ese nombre";
                }


                cout<<"El total es de "<<endl;
                cout.setf(ios::fixed);
                cout.precision(4);
                cout <<setw(10) <<'$'<< total <<endl;



            }
            }catch (const char *e) {
                cout<<e;
            }
            fclose(encabezadoVentas);
            fclose(detalle_venta);
            break;
    }
        cout << "a. Registro de Ventas" << endl;
        cout << "b. Total por articulo" << endl;
        cout << "c. Detalle por cliente" << endl;
        cout << "d. Salir" << endl;
        cin >> opcion;
    }
    return 0;
}

bool existeNumero(char arrf[][20], char buscar[20], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(arrf[i], buscar) == 0)
        {
            return true;
        }
    }
    return false;
}

bool buscarArchivo(char numeroVentaf[100], FILE *archivo)
{
    char numeroVenta[100], nombre[80], fecha[50];
    int claveCliente;
    rewind(archivo);
    while (fscanf(archivo, "%s %d |%[^|]| %s", numeroVenta, &claveCliente, nombre, fecha) == 4)
    {

        if (strcmp(numeroVentaf, numeroVenta) == 0) 
        {
            return true;
        }
    }
    return false;
}
