#include "imagen.h"


void Rota (double angulo) {
    double coseno = cos(angulo);
    double seno = sin(angulo);

    //Para obtener las dimensiones de la imagen
    int rcorners[4], ccorners[4];
    int newimgrows, newimgcols;
    double new_row_min, new_col_min, new_row_max, new_col_max;
    double inter, inter1;

    rcorners[0] = 0;
    rcorners[1] = 0;
    ccorners[0] = 0;
    ccorners[2] = 0;

    rcorners[2] = num_filas() -1;
    rcorners[3] = num_filas() -1;
    ccorners[1] = num_cols() -1;
    ccorners[3] = num_cols() -1;

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
	inter1 = -rcorners[count] * seno + ccorners[count] * coseno;
	   
	if (inter1 < new_col_min)
	    new_col_min = inter1;	
	if (inter1 > new_col_max)
	    new_col_max = inter1;
    }
    
    newimgrows = (unsigned) ceil((double) new_row_max-new_row_min);
    newimgcols = (unsigned) ceil((double) new_col_max-new_col_min);
   

    // Rota cada pixel de la imagen.
    // Copiará la imagen rotada en la imagen implícita.
    Imagen Iout(newimgrows,newimgcols);
    
    for (int rows = 0; rows<newimgrows; ++rows) {
	for (int cols = 0; cols<newimgcols; ++cols) {
	    float oldrowcos = ((float)rows + new_row_min) * cos(-rads);
	    float oldrowsin = ((float)rows + new_row_min) * sin(-rads);
	    float oldcolcos = ((float)cols + new_col_min) * cos(-rads);
	    float oldcolsin = ((float)cols + new_col_min) * sin(-rads);
	    float old_row =  oldrowcos + oldcolsin;
	    float old_col = -oldrowsin + oldcolcos;

	    old_row = ceil((double) old_row);
	    old_col = ceil((double) old_col);
	    if (old_row >= 0 and old_row < num_filas() and old_col >= 0 and old_col < num_cols())
		Iout[rows][cols] = operator[old_row][old_col];
	    else
		Iout[rows][cols].red = Iout[rows][cols].green = Iout[rows][cols].blue = 255;
	}
    }

    (*this) = Iout;
}


/**
 * Funciones de entrada y salida.
 * Se incluyen funciones de lectura y escritura de las imágenes.
 */

istream& operator >> (istream& input, Imagen& leida) {
    TipoImagen tipo = leerTipoImagen (input);
    int filas, columnas;
    Buffer buffer;

    // Intenta lectura según el tipo leído.
    switch (tipo) {
    case IMAGEN_PPM: buffer = leerImagenPPM(input, filas, columnas); break;
    case IMAGEN_PGM: buffer = leerImagenPGM(input, filas, columnas); break;
    case default: input.setstate (ios::failbit); return input;
    }
    
    // Lleva el buffer a la matriz de la imagen.
    // Controla el tamaño del buffer según filas y columnas.
    leida = Imagen(filas, vector<Imagen::Pixel>(columnas));
  
    if (tipo == IMAGEN_PPM) {
	int posicion_buffer = 0;
	
	for (int i=0; i<filas; ++i) {
	    for (int j=0; j<columnas; ++j) {
		Pixel actual = leida[i][j];
		actual.red   = buffer[posicion_buffer++];
		actual.green = buffer[posicion_buffer++];
		actual.blue  = buffer[posicion_buffer++];
		actual.transparencia = 0;
	    }
	}
    }
    
    if (tipo == IMAGEN_PGM) {
	int posicion_buffer = 0;
	
	for (int i=0; i<filas; ++i) {
	    for (int j=0; j<columnas; ++j) {
		Pixel actual = leida[i][j];
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
