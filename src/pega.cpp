#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "imagen.h"
using namespace std;

/**
 * Programa para el pegado de imágenes.
 * Dada una imagen de fondo, una segunda imagen y una máscara,
 * superpone la segunda imagen sobre la primera usando la máscara.
 */
int main (int argc, char* argv []) {
    // Mensajes del programa.
    typedef const string Mensaje;
    Mensaje MSG_ERROR = "Error. Uso incorrecto del programa.\n";
    Mensaje MSG_USO   = "El programa recibe 7 parámetros:\n";
    Mensaje MSG_PAR1  = "1. Imagen de fondo.\n";
    Mensaje MSG_PAR2  = "2. Imagen a pegar.\n";
    Mensaje MSG_PAR3  = "3. Máscara de la imagen a pegar.\n";
    Mensaje MSG_PAR4  = "4. Nombre de la imagen de salida.\n";
    Mensaje MSG_PAR5  = "5. Desplazamiento por filas.\n";
    Mensaje MSG_PAR6  = "6. Desplazamiento por columnas.\n";
    Mensaje MSG_PAR7  = "7. Pegado opaco (0) o transparente (1).\n";

    // Comprueba el uso correcto de los argumentos.
    if (argc != 8) {
	cerr << MSG_ERROR << MSG_USO;
	cerr << MSG_PAR1
	     << MSG_PAR2
	     << MSG_PAR3
	     << MSG_PAR4
	     << MSG_PAR5
	     << MSG_PAR6
	     << MSG_PAR7;

	return -1;
    }

    // Lee los argumentos.
    string archivo_fondo = argv[1];
    string archivo_imagen = argv[2];
    string archivo_mascara = argv[3];
    string archivo_salida = argv[4];


    // Obtiene las imágenes de los ficheros indicados.
    Imagen fondo;
    Imagen pegado;
    Imagen mascara;

    fstream input_fondo (archivo_fondo);    
    entrada >> fondo;
}
