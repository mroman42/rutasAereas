#ifndef _PUNTO_H
#define _PUNTO_H

#include <string>
#include <iostream>

using namespace std;

/**
 * T.D.A. Punto
 * Contiene la información de un punto del mapa,
 * codificando su ubicación por longitud y latitud, y su descripción.
 */
class Punto {
private:
    double latitud;
    double longitud;

public:
    /**
     * Constructor del punto.
     */
    Punto (double latit = 0, double longit = 0)
	: latitud(latit), longitud(longit)
    {}

    /**
     * Constructor de copia.
     */
    Punto (const Punto& otro){
        latitud = otro.latitud;
        longitud = otro.longitud;
    }

    /*
     * Devuelve una referencia a la latitud del punto
     */
    inline double& Latitud(){
        return latitud;
    }

    /*
     * Devuelve una referencia a la longitud del punto
     */
    inline double& Longitud(){
        return longitud;
    }

    /**
     * Comparación entre puntos.
     */
    inline bool operator < (const Punto& otro) const {
	    bool latitud_menor = latitud < otro.latitud;
	    bool latitud_igual = latitud == otro.latitud;
	    bool longitud_menor = longitud < otro.longitud;

	    return latitud_menor or (latitud_igual and longitud_menor);
    }

    friend istream& operator >> (istream& input, Punto& leido);
    friend ostream& operator << (ostream& output, const Punto& leido);
};


#endif
