#include "punto.h"

using namespace std;


istream& operator >> (istream& input, Punto& leido) {
    /**
     * El formato de un punto será:
     *    (<latitud>,<longitud>)
     * Leemos cada una de las partes de la ruta. 
     */
    char separador;
    input >> separador;

    if (separador != '(') {
	    input.setstate(ios::failbit);
	    return input;
    }

    input >> leido.latitud;
    input >> separador;

    if (separador != ',') {
	    input.setstate(ios::failbit);
	    return input;
    }

    input >> leido.longitud;
    input >> separador;

    if (separador != ')') {
	    input.setstate(ios::failbit);
	    return input;
    }

    return input;
}


ostream& operator << (ostream& output, const Punto& punto) {
    /**
     * Formato de salida:
     *    (<latitud>,<longitud>)
     */
    cout << '(' << punto.latitud << ',' << punto.longitud << ')';

    return output;
}

