#ifndef _PAIS_H
#define _PAIS_H

#include <string>
#include <iostream>
#include "punto.h"

using namespace std;

/**
 * T.D.A. Pais
 * Contiene la información de un pais del mapa,
 * codificando su ubicación por longitud y latitud, su nombre y su bandera.
 */
class Pais {
private:
    Punto ubicacion;
    string nombre;
    string bandera;

public:
    /**
     * Constructor del pais.
     */
    Pais (Punto place, string name, string flag)
	: ubicacion(place), nombre(name), bandera(flag)
    {}

    friend istream& operator >> (istream& input, Pais& leido);
};


#endif
