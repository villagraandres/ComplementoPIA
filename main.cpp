#include <iostream>
#include <regex>
#include <cstring>

using namespace std;

bool buscarArchivo(char numeroVenta[100],FILE *);
bool existeNumero(int *arrf,int,int );

int main() 
{
    char opcion;
    FILE *encabezadoVentas,*detalle_venta;
    char numeroVenta[100], nombre[80], fecha[50],descripcion[100],cantidad,continuar;
    int claveCliente,consecutivo=1,claveArticulo,vistos[150];
    float precio;
    regex patronVenta("^V\\d{2}-\\d$");
    cout<<"a.Registro de Ventas"<<endl;
    cout<<"b.Total por articulo"<<endl;
    cout<<"c. Detalle por cliente"<<endl;
    cout<<"d. Salir"<<endl;
    cin>>opcion;
    switch (opcion) 
    {
        case 'a':
            try 
                {
                encabezadoVentas=fopen("encabezado_venta.txt","a+");
                detalle_venta=fopen("detalle_venta.txt.","a+");
                if(detalle_venta==NULL || encabezadoVentas==NULL) 
                {
                    throw "Error al crear el archivo";
                }
                else 
                {
                    do 
                    {
                        cout<<"Ingresa el numero de venta"<<endl;
                        cin>>numeroVenta;
                    }
                    while(!regex_match(numeroVenta,patronVenta) or buscarArchivo(numeroVenta,encabezadoVentas));

                    do 
                    {
                        cout<<"Ingrese la clave del cliente"<<endl;
                        cin>>claveCliente;
                        if(claveCliente<100 or claveCliente>200) 
                        {
                            cout<<"Clave invalida, debe estar entre 100 y 200"<<endl;
                        }
                    }
                    while(claveCliente<100 or claveCliente>200);

                    cout<<"Ingrese el nombre"<<endl;
                    cin.ignore();
                    cin.getline(nombre, sizeof(nombre));
                    cout<<"Ingrese la fecha"<<endl;
                    cin.ignore();
                    cin.getline(fecha, sizeof(fecha));
                    if(cin.fail()) 
                    {
                        throw "Se han ingresado datos invalidos";
                    }
                    fprintf(encabezadoVentas,"%s %d |%s| %s\n",numeroVenta,claveCliente,nombre,fecha);

                    do 
                    {
                        do 
                        {
                            cout<<"Ingrese la clave del articulo"<<endl;
                            cin>>claveArticulo;
                        }
                        while(claveArticulo>100 or claveArticulo<1 or existeNumero(vistos,claveArticulo,consecutivo));

                        cout<<"Ingrese la descripcion"<<endl;
                        cin.ignore();
                        cin.getline(descripcion, sizeof(descripcion));

                        do 
                        {
                            cout<<"Ingrese la cantidad deseada"<<endl;
                            cin>>cantidad;
                        }
                            while(cantidad<0);

                        do 
                        {
                            cout<<"Ingrese el precio del articulo"<<endl;
                            cin.ignore();
                            cin>>precio;
                        }
                        while(precio<0);
                        vistos[consecutivo]=claveArticulo;

                        fprintf(detalle_venta,"%s %d %d |%s| %d %f\n",numeroVenta,consecutivo,claveArticulo,descripcion,cantidad,precio);
                        consecutivo++;

                        cout<<"Desea continuar? S:si N:no";
                        cin.ignore();
                        cin>>continuar;
                    }
                    while(continuar!='N');
                }
            }
            catch (const char *e) 
            {
                cout<<e;
            }
            fclose(encabezadoVentas);
            fclose(detalle_venta);
    }
    return 0;
}

bool existeNumero(int *arrf,int buscar,int tam ) 
{
    int i;
        for(i=0;i<tam;i++) 
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

    while(fscanf(archivo,"%s %d |%s| %s",&numeroVenta,&claveCliente,&nombre,&fecha)==4) 
    {
        if(strcmp(numeroVentaf,numeroVenta)==0) 
        {
            return true;
        }
    }
    return false;
}
