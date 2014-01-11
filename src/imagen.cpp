#include "imagen.h"

using namespace std;


void Imagen::pega (const Imagen& imagen, const Imagen& mascara, const bool transparente, const int offset_horizontal, const int offset_vertical) {
    // Comprueba que la imagen y la máscara tengan las mismas dimensiones.
    int filas = imagen.numFilas();
    int columnas = imagen.numColumnas();
    if (filas != mascara.numFilas() or columnas != mascara.numColumnas())
	return;

    // Copia los pixeles de la imagen dada en la imagen actual.
    if (transparente) {
	for (int i=0; i<filas; ++i)
	    for (int j=0; j<columnas; ++j)
		if (mascara[i][j].transparencia == 255)
		    at(i + offset_vertical).at(j + offset_horizontal) = imagen[i][j];
    }
    else {
	for (int i=0; i<filas; ++i) {
	    for (int j=0; j<columnas; ++j) {
		if (mascara[i][j].transparencia == 255) {
		    Pixel& actual = at(i+offset_vertical).at(j+offset_horizontal);
		    Pixel nuevo = imagen[i][j];

		    actual.red = actual.red / 2 + nuevo.red / 2;
		    actual.blue = actual.blue / 2 + nuevo.blue / 2;
		    actual.green = actual.green / 2 + nuevo.green / 2;
		}
	    }
	}	    
    }
    
}

void Imagen::rota (double angulo) {
    // Transforma a radianes y calcula seno y coseno.
    double radianes = angulo * M_PI / 180.0;
    double coseno = cos(radianes);
    double seno = sin(radianes);

    //Para obtener las dimensiones de la imagen
    int rcorners[4], ccorners[4];
    int newimgrows, newimgcols;
    double new_row_min, new_col_min, new_row_max, new_col_max;
    double inter, inter1;

    rcorners[0] = 0;
    rcorners[1] = 0;
    ccorners[0] = 0;
    ccorners[2] = 0;

    rcorners[2] = numFilas() - 1;
    rcorners[3] = numFilas() - 1;
    ccorners[1] = numColumnas() - 1;
    ccorners[3] = numColumnas() - 1;

    new_row_min = 0;
    new_col_min = 0;
    new_row_max = 0;
    new_col_max = 0;

    newimgrows = 0;
    newimgcols = 0;

    for (int count = 0; count < 4; ++count) {
	inter = rcorners[count] * coseno + ccorners[count] * seno;
	if (inter < new_row_min)
	    new_row_min = inter;
	if (inter > new_row_max)
	    new_row_max = inter;
	
	inter1 = - rcorners[count] * seno + ccorners[count] * coseno;
	if (inter1 < new_col_min)
	    new_col_min = inter1;	
	if (inter1 > new_col_max)
	    new_col_max = inter1;
    }
    
    newimgrows = (unsigned) ceil((double) new_row_max - new_row_min);
    newimgcols = (unsigned) ceil((double) new_col_max - new_col_min);
    
    
    // Rota cada pixel de la imagen.
    // Copiará la imagen rotada en la imagen implícita.
    Imagen Iout(newimgrows, newimgcols);
    Iout.tipo = tipo;
    
    for (int rows = 0; rows<newimgrows; ++rows) {
	for (int cols = 0; cols<newimgcols; ++cols) {
	    // Busca el pixel que, rotado, da como imagen el pixel actual.
	    float oldrowcos = ((float) rows + new_row_min) * coseno;
	    float oldrowsin = ((float) rows + new_row_min) * seno;
	    float oldcolcos = ((float) cols + new_col_min) * coseno;
	    float oldcolsin = ((float) cols + new_col_min) * seno;
	    float old_row = oldrowcos - oldcolsin;
	    float old_col = oldrowsin + oldcolcos;
	    
	    old_row = ceil((double) old_row);
	    old_col = ceil((double) old_col);
	    
	    // Si existía en la imagen original, lo copia en la nueva imagen.
	    if (old_row >= 0 and old_row < numFilas() and old_col >= 0 and old_col < numColumnas())
	    	Iout[rows][cols] = at(old_row).at(old_col);
	    else {
	    	Iout[rows][cols].red = Iout[rows][cols].green = Iout[rows][cols].blue = 255;
		Iout[rows][cols].transparencia = 0;
	    }
	}
    }

    (*this) = Iout;
}



/**
 * Funciones de lectura de las imágenes.
 * Operador de lectura y funciones auxiliares.
 */

istream& operator >> (istream& input, Imagen& leida) {
    Imagen::TipoImagen tipo = Imagen::leerTipoImagen(input);
    Imagen::Buffer buffer;
    int filas, columnas;

    // Intenta lectura según el tipo leído.
    switch (tipo) {
    case Imagen::IMAGEN_PPM: buffer = Imagen::leerImagenPPM(input, filas, columnas); break;
    case Imagen::IMAGEN_PGM: buffer = Imagen::leerImagenPGM(input, filas, columnas); break;
    default: input.setstate (ios::failbit); return input;
    }
    
    // Lleva el buffer a la matriz de la imagen.
    // Controla el tamaño del buffer según filas y columnas.
    leida = Imagen(filas, columnas);
    leida.tipo = tipo;
    
    if (tipo == Imagen::IMAGEN_PPM) {
	int posicion_buffer = 0;

	for (int i=0; i<filas; ++i) {
	    for (int j=0; j<columnas; ++j) {
		Pixel& actual = leida[i][j];
		actual.red   = buffer[posicion_buffer++];
		actual.green = buffer[posicion_buffer++];
		actual.blue  = buffer[posicion_buffer++];
		actual.transparencia = 0;
	    }
	}
    }
    
    if (tipo == Imagen::IMAGEN_PGM) {
	int posicion_buffer = 0;
	
	for (int i=0; i<filas; ++i) {
	    for (int j=0; j<columnas; ++j) {
		Pixel& actual = leida[i][j];
		actual.red   = buffer[posicion_buffer];
		actual.green = buffer[posicion_buffer];
		actual.blue  = buffer[posicion_buffer];
		actual.transparencia = 0;
		++posicion_buffer;
	    }
	}	
    }

    return input;
}


Imagen::TipoImagen Imagen::leerTipoImagen (istream& input) {
    /**
     * El tipo de imagen viene dado por los dos primeros caracteres.
     * El primer caracter debe ser una P y el segundo debe ser un número.
     *  - En caso de que sea 5, será imagen PGM.
     *  - En caso de que sea 6, será imagen PPM.
     * Por defecto, se considera el tipo desconocido de imagen.
     */
    TipoImagen tipo = DESCONOCIDA;
    char c1, c2;
  
    if (input) {
	c1 = input.get();
	c2 = input.get();

	if (input and c1 == 'P') {
	    switch (c2) { 
	    case '5': tipo = IMAGEN_PGM; break;
	    case '6': tipo = IMAGEN_PPM; break;
	    }
	}
    }

    return tipo;

}


Imagen::Buffer Imagen::leerImagenPPM (istream& input, int& filas, int& columnas) {
    // Si puede leer la cabecera correctamente,
    // reserva espacio para el buffer y lo vuelca directamente.
    if (LeerCabecera (input, filas, columnas)) {
	int tamanio_buffer = filas * columnas * 3;
	Buffer buffer = new unsigned char[tamanio_buffer]; 
    
	if (input.read((char*) buffer, tamanio_buffer))
	    return buffer;
    }

    // Caso de lectura errónea.
    filas = 0;
    columnas = 0;
    return NULL;
}

Imagen::Buffer Imagen::leerImagenPGM (istream& input, int& filas, int& columnas) {
    // Si puede leer la cabecera correctamente,
    // reserva espacio para el buffer y lo vuelca directamente.
    if (LeerCabecera (input, filas, columnas)) {
	int tamanio_buffer = filas * columnas;
	Buffer buffer = new unsigned char [tamanio_buffer]; 
    
	if (input.read((char*) buffer, tamanio_buffer))
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
        input.get();
        return true;
    }
    
    return false;
}


void Imagen::saltarComentarios (istream& input) {
    // Salta todas las líneas que comiencen con #.
    static const int SALTO_MAXIMO = numeric_limits<streamsize>::max();
    while (saltarSeparadores(input) == '#')
	input.ignore (SALTO_MAXIMO, '\n');
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



/**
 * Funciones de escritura de las imágenes.
 * Operador de escritura y funciones auxiliares.
 */

ostream& operator << (std::ostream& output, const Imagen& imagen) {
    static const int MAXIMO = 225; 
    int filas = imagen.numFilas();
    int columnas = imagen.numColumnas();

    // Escribe como imagen PPM.
    if (imagen.tipo == Imagen::IMAGEN_PPM) {
	if (output) {
	    output << "P6" << endl;
	    output << filas << ' ' << columnas << endl;
	    output << MAXIMO << endl;
	
	    for (int i=0; i<filas; ++i)
		for (int j=0; j<columnas; ++j) {
		    const Pixel& actual = imagen[i][j];
		    output << actual.red << actual.green << actual.blue;
		}
	}
    }

    // Escribe como imagen PGM.
    else if (imagen.tipo == Imagen::IMAGEN_PGM) {
	if (output) {
	    output << "P5" << endl;
	    output << filas << ' ' << columnas << endl;
	    output << MAXIMO << endl;

	    for (int i=0; i<filas; ++i)
		for (int j=0; j<columnas; ++j) {
		    const Pixel& actual = imagen[i][j];
		    output << actual.transparencia;
		}
	}
    }

    // Escribe un error si se desconoce el tipo de la imagen.
    else {
	output << "ERROR: Tipo desconocido.\n";
    }

    return output;
}
