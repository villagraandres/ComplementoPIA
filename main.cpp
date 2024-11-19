#include <iostream>
#include <regex>
using namespace std;
bool buscarArchivo(char numeroVenta[100],FILE *);
int main() {
    char opcion;
    cout<<"a.Registro de Ventas"<<endl;
    cout<<"b.Total por articulo"<<endl;
    cout<<"c. Detalle por cliente"<<endl;
    cout<<"d. Salir"<<endl;
    cin>>opcion;
    switch (opcion) {
        case 'a':
            FILE *encabezadoVentas,*detalle_venta;
            char numeroVenta[100], nombre[80], fecha[50];
            int claveCliente;
            regex patronVenta("^V\\d{2}-\\d$");

            try {
                encabezadoVentas=fopen("encabezado_venta.txt","a+");
                detalle_venta=fopen("detalle_venta.txt.","a+");
                if(detalle_venta==NULL || encabezadoVentas==NULL) {
                    throw "Error al crear el archivo";
                }else {

                    do {
                        cout<<"Ingresa el numero de venta"<<endl;
                        cin>>numeroVenta;
                    }while(!regex_match(numeroVenta,patronVenta) and !buscarArchivo(numeroVenta,encabezadoVentas));

                    do {
                        cout<<"Ingrese la clave del cliente"<<endl;
                        cin>>claveCliente;
                        if(claveCliente<100 or claveCliente>200) {
                            cout<<"Clave invalida, debe estar entre 100 y 200"<<endl;

                        }
                    }while(claveCliente<100 or claveCliente>200);

                    cout<<"Ingrese el nombre"<<endl;
                    cin>>nombre;
                    cout<<"Ingrese la fecha"<<endl;
                    cin>>fecha;

                    fprintf(encabezadoVentas,"%s %d %s %s",numeroVenta,claveCliente,nombre,fecha);


                    do {
                        cout<<"Ingrese"
                    }
                }
            }catch (const char *e) {
                cout<<e;
            }
            fclose(encabezadoVentas);
    }
    return 0;
}
bool buscarArchivo(char numeroVenta[100], FILE *archivo) {
    return true;
}