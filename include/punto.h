/**
 * Práctica: Rutas Aéreas
 * Asignatura: Estructura de Datos(2º DGIIM)
 * Autores: Óscar Bermúdez Garrido y Mario Román García
 */
#ifndef _PUNTO_H
#define _PUNTO_H

#include <string>
#include <iostream>

using std::string;
using std::istream;

/**
 * T.D.A. Punto
 * Contiene la información de un punto del mapa,
 * codificando su ubicación por longitud y latitud.
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


    /**
     * Lee un punto.
     * @param input Flujo de lectura.
     * @param leido Punto donde se leerá.
     */
    friend std::istream& operator >> (std::istream& input, Punto& leido);

    /**
     * Muestra por pantalla el bucle.
     * @param output Flujo de salida.
     * @param leido Punto en el que se escribirá.
     */
    friend std::ostream& operator << (std::ostream& output, const Punto& leido);
};

/**
 * Retira espacios, tabulaciones y saltos de línea de un flujo.
 * @param input Flujo de entrada.
 */
void retirarEspacios (istream& input);

#endif
