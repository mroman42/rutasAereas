#include "imagen.h"

istream& operator >> (istream& input, Imagen& leida) {
    
    return input;
}


TipoImagen LeerTipoImagen (istream& input) {
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
