#ifndef _PUNTO_H
#define _PUNTO_H

#include <string>
#include <iostream>

using std::string;
using std::istream;

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
    Punto (double latit = 0, double longit = 0)
	: latitud(latit), longitud(longit)
    {}

    /**
     * Comparación entre puntos.
     */
    inline bool operator < (const Punto& otro) const {
	bool latitud_menor = latitud < otro.latitud;
	bool latitud_igual = latitud == otro.latitud;
	bool longitud_menor = longitud < otro.longitud;

	return latitud_menor or (latitud_igual and longitud_menor);
    }

    friend std::istream& operator >> (std::istream& input, Punto& leido);
};


#endif
