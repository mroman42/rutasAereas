#include "almacen.h"
#include <fstream>

using namespace std;

/**
 * Ejemplo de uso del almacén de rutas para la práctica 3.
 */

int main(int argc, char * argv[]){
    // Lectura de argumentos
    if (argc != 2) {
	cout << "Introduzca como único argumento el fichero de entrada." << endl;
	return 0;
    }

    // Apertura del fichero de entrada.
    ifstream archivo (argv[1]);
    if (!archivo) {
	cout << "No puedo abrir el fichero " << argv[1] << endl;
	return 0;
    }



    // Creamos un almacén donde leemos rutas y puntos de interés.
    // Escribimos el interior del almacén.
    Almacen almacen;
    archivo >> almacen;

    for (Almacen::iterator it = almacen.begin(); it != almacen.end(); ++it) {
	Codigo codigo = it->first;
	Ruta& ruta = it->second;
	cout << "Código " << codigo << ": ";

	for (Ruta::iterator itr = ruta.begin(); itr != ruta.end(); ++itr)
	    cout << *itr << " ";

	cout << endl;
    }
}
