#ifndef _PAIS_H
#define _PAIS_H

#include <string>
#include <iostream>
#include "punto.h"

using std::string;

/**
 * T.D.A. Pais
 * Contiene la información de un pais del mapa,
 * codificando su ubicación por longitud y latitud, su nombre y su bandera.
 */
class Pais {
private:
    /**
     * Coordenadas del país sobre el mapa.
     */
    Punto ubicacion;
    
    /**
     * Nombre del país.
     */
    string nombre;

    /**
     * Ruta de la imagen a la bandera del país.
     */
    string bandera;

public:
    /**
     * Constructor del pais.
     */
    Pais(){}

    /**
     * Constructor del pais.
     */
    Pais (Punto place, string name, string flag)
	: ubicacion(place), nombre(name), bandera(flag)
    {}

    /*
     * Devuelve su posición
     */
    inline Punto Ubicacion(){
        return ubicacion;
    }

    /*
     * Devuelve su nombre
     */
    inline string Nombre(){
        return nombre;
    }

    /*
     * Devuelve su bandera
     */
    inline string Bandera(){
        return bandera;
    }


    friend std::istream& operator >> (std::istream& input, Pais& leido);
    friend std::ostream& operator << (std::ostream& output, const Pais& pais);
};


#endif
