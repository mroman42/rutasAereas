#ifndef _PUNTO_H
#define _PUNTO_H

#include <string>

/**
 * T.D.A. Punto
 * Contiene la información de un punto del mapa,
 * codificando su ubicación por longitud y latitud, y su descripción.
 */
class Punto {
private:
    double latitud;
    double longitud;
    string descripcion;

public:
    /**
     * Constructor del punto.
     */
    Punto (double latit = 0, double longit = 0, const string& descr = "")
	: latitud(latit), longitud(longit), descripcion(descr)
    {}


    friend istream& operator >> (istream& input, Punto& leido);
};


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
}

#endif
