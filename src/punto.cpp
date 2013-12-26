#include "punto.h"

using namespace std;


istream& operator >> (istream& input, Punto& leido) {
    /**
     * El formato de un punto será:
     *    (<latitud>,<longitud>)
     * Leemos cada una de las partes de la ruta. 
     */
    input.ignore();
    input >> leido.latitud;
    input.ignore();
    input >> leido.longitud;
    input.ignore();

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
