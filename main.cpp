#include <iostream>
#include <regex>
#include <cstring>
#include <iomanip>
using namespace std;

bool buscarArchivo(char numeroVenta[100], FILE *);
bool existeNumero(int *arrf, int, int);

int main() 
{
    char opcion;
    FILE *encabezadoVentas, *detalle_venta;
    char numeroVenta[100], numeroVenta2[100], nombre[80], nombre2[80], fecha[50], descripcion[100], continuar;
    int claveCliente, consecutivo = 1, claveArticulo, vistos[150],cantidad;
    float precio,total=0;
    bool encontrado = false;
    regex patronVenta("^V\\d{2}-[1-9]$");
    regex patronNombre("^[a-zA-Z0-9 ]+$");

    cout << "a. Registro de Ventas" << endl;
    cout << "b. Total por articulo" << endl;
    cout << "c. Detalle por cliente" << endl;
    cout << "d. Salir" << endl;
    cin >> opcion;
    switch (opcion) 
    {
        case 'a':
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

                    cout << "Ingrese el nombre" << endl;
                    cin.ignore();
                    cin.getline(nombre, sizeof(nombre));
                    cout << "Ingrese la fecha" << endl;
                    cin.getline(fecha, sizeof(fecha));
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
                        while (claveArticulo > 100 || claveArticulo < 1 || existeNumero(vistos, claveArticulo, consecutivo));

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
                        vistos[consecutivo] = claveArticulo;

                        fprintf(detalle_venta, "%s %d %d |%s| %d %f\n", numeroVenta, consecutivo, claveArticulo, descripcion, cantidad, precio);
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
            fclose(encabezadoVentas);
            fclose(detalle_venta);
            break;

        case 'b':
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
                    printf("Ingrese el nombre del usuario\n");
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

                    }
                }

                if (!encontrado)
                {
                    throw "No se encontro ningun resgitro con ese nombre";
                }

                rewind(detalle_venta);
                while (fscanf(detalle_venta, "%s %d %d |%[^|]| %d %f", numeroVenta, &consecutivo, &claveArticulo, descripcion, &cantidad, &precio) == 6)
                {
                    if (strcmp(numeroVenta, numeroVenta2) == 0)
                    {
                        total+=precio;
                    }
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
    return 0;
}

bool existeNumero(int *arrf, int buscar, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (*(arrf + i) == buscar)
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
