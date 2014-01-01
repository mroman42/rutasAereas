#include "imagen.h"

istream& operator >> (istream& input, Imagen& leida) {
    
    return input;
}


TipoImagen Imagen::leerTipoImagen (istream& input) {
    /**
     * El tipo de imagen viene dado por los dos primeros caracteres.
     * El primer caracter debe ser una P y el segundo debe ser un número.
     *  - En caso de que sea 5, será imagen PGM.
     *  - En caso de que sea 6, será imagen PPM.
     * Por defecto, se considera el tipo desconocido de imagen.
     */
    TipoImagen tipo = IMG_DESCONOCIDO;
    char c1, c2;
  
    if (input) {
	c1 = input.get();
	c2 = input.get();

	if (input and c1 == 'P')
	    switch (c2) {
	    case '5': res = IMG_PGM; break;
	    case '6': res = IMG_PPM; break;
	    }
    }

    return res;

}


Buffer Imagen::leerImagenPPM (istream& input, int& filas, int& columnas) {
    // Si puede leer la cabecera correctamente,
    // reserva espacio para el buffer y lo vuelca directamente.
    if (LeerCabecera (input, filas, columnas)) {
	int tamanio_buffer = filas * columnas * 3;
	Buffer buffer = new char [tamanio_buffer]; 
    
	if (input.read(buffer, tamanio_buffer))
	    return buffer;
    }

    // Caso de lectura errónea.
    filas = 0;
    columnas = 0;
    return NULL;
}

Buffer Imagen::leerImagenPGM (istream& input, int& filas, int& columnas) {
    // Si puede leer la cabecera correctamente,
    // reserva espacio para el buffer y lo vuelca directamente.
    if (LeerCabecera (input, filas, columnas)) {
	int tamanio_buffer = filas * columnas;
	Buffer buffer = new char [tamanio_buffer]; 
    
	if (input.read(buffer, tamanio_buffer))
	    return buffer;
    }
  
    // Caso de lectura errónea.
    filas = 0;
    columnas = 0;
    return NULL;
}



bool Imagen::LeerCabecera (istream& input, int& filas, int& columnas) {
    int maxvalor;
    saltarComentarios(input);
    input >> columnas >> filas >> maxvalor;
    
    if (input and filas > 0 and filas < 5000 and columnas > 0 and columnas < 5000) {
        f.get();
        return true;
    }
    
    return false;
}


void Imagen::saltarComentarios (istream& input) {
    // Salta todas las líneas que comiencen con #.
    static const int SALTO_MAXIMO = numeric_limits<streamsize>::max();
    while (saltarSeparadores(input) == '#')
	input.ignore (TAMANIO_SALTO, '\n');
}


char Imagen::saltarSeparadores (istream& input) {
    // Extrae caracteres hasta que alguno sea distinto a un espacio.
    char leido;

    do
	leido = input.get();
    while (isspace(leido));
    input.putback(leido);

    return leido;
}
