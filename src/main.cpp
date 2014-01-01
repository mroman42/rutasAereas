#include "almacen.h"
#include "paises.h"
#include <fstream>

using namespace std;

/**
 * Ejemplo de uso del almacén de rutas para la práctica 3.
 */

int main(int argc, char * argv[]){
    // Lectura de argumentos
    if (argc != 3) {
	cout << "Introduzca como argumentos los ficheros de entrada.\nPrimero, el almacén, y luego, los países." << endl;
	return 0;
    }

    // Apertura de los ficheros de entrada.
    ifstream archivo_almacen (argv[1]);
    ifstream archivo_paises (argv[2]);
    if (!archivo_almacen) {
	cout << "No puedo abrir el fichero" << argv[1] << endl;
	return 0;
    }
    if (!archivo_paises) {
	cout << "No puedo abrir el fichero" << argv[2] << endl;
	return 0;
    }

    // Creamos un almacén donde leemos rutas y puntos de interés.
    // Escribimos el interior del almacén.
    Almacen almacen;
    archivo_almacen >> almacen;

    for (Almacen::iterator it = almacen.begin(); it != almacen.end(); ++it) {
	Codigo codigo = it->first;
	Ruta& ruta = it->second;
	cout << "Código " << codigo << ": ";

	for (Ruta::iterator itr = ruta.begin(); itr != ruta.end(); ++itr)
	    cout << *itr << " ";

	cout << endl;
    }


    // Pide al usuario una consulta de ruta.
    Codigo codigo_pedido;
    cout << "Introduzca el código de una ruta: ";
    cin >> codigo_pedido;
    cout << "La ruta pedida se escribe como: " << endl;
    cout << codigo_pedido << '\t' << almacen.obtenerRuta (codigo_pedido) << endl;
    cout << endl;


    // Pide al usuario la consulta de un punto.
    Punto punto;
    cout << "Introduzca un punto en formato (latitud,longitud): ";
    cin >> punto;

    Descripcion descripcion = almacen.obtenerDescripcion(punto);
    Rutas rutas = almacen.obtenerRutas(punto);
    cout << "La descripción del punto " << punto << " es: " << descripcion << endl;
    cout << "Las rutas que pasan por el punto son: ";

    for (Rutas::iterator it = rutas.begin(); it != rutas.end(); ++it)
	cout << *it << ' ';

    cout << endl;


    // Creamos un conjunto de paises donde leemos los países y su información.
    // Escribimos el interior del conjunto.
    Paises conjunto;
    archivo_paises >> conjunto;

    //Los mostramos todos
    cout << conjunto; 


    // Pide al usuario una consulta de un país.
    Nombre pedido;
    cout << "Introduzca el nombre de un país: ";
    cin >> pedido;

    cout << "Información del país pedido:\n";
    cout << Pais(conjunto.obtenerPais(pedido));

    return 0;  
}
