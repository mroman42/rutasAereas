#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "imagen.h"
using namespace std;


/**
 * Programa para la rotación de imágenes.
 * Dada una imagen y un ángulo de rotación, permite al usuario obtener
 * una nueva imagen que es una versión rotada de la imagen original.
 */
int main(int argc, char* argv []) {
    // Mensajes del programa.
    string MSG_ERROR = "Error. Uso incorrecto del programa. ";
    string MSG_USO = "El programa recibe cuatro argumentos. \n rota \t<imagen>\t<angulo>\t<imagen_salida>\n";

    // Comprueba el uso correcto del programa.
    if (argc != 4) {
	cerr << MSG_ERROR;
	cerr << MSG_USO;
	return -1;
    } 

    // Lee los argumentos.
    string archivo_imagen = argv[1];
    string archivo_salida = argv[3];
    float grados_rotacion = strtod(argv[2], NULL);
    
    
    // Lee la imagen del archivo inicial.
    Imagen imagen_leida;
    fstream entrada (archivo_imagen);
    entrada >> imagen_leida;
    entrada.close();

    // Rota los grados pedidos.
    imagen_leida.rota(grados_rotacion);


    // Escribe la imagen en el archivo de salida.
    fstream salida (archivo_salida, fstream::out);
    salida << imagen_leida;
    salida.close();
}
