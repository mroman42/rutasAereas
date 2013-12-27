#ifndef _ALMACEN_H
#define _ALMACEN_H

#include <string>
#include <iostream>
#include <list>
#include <map>
#include "punto.h"

using namespace std;

typedef string Descripcion;
typedef string Codigo;
typedef list<Punto> Ruta;
typedef list<Codigo> Rutas;


/**
 * T.D.A. Almacén
 * Contiene todas las rutas sobre un mapa, así como los puntos
 * destacados del mismo, que formarán parte de las rutas.
 */
class Almacen {
private:
    /**
     * Información relativa al punto y contenida en un almacén.
     * Un punto contará con una descripción y una lista de rutas asociadas.
     */
    struct InfoPunto {
	    /**
	     * Descripción del punto.
	     */
	    Descripcion descripcion;

	    /**
	     * Listado de rutas asociadas a un punto.
	     */
	    Rutas rutas;
    };

    /**
     * Mapa de puntos del almacén.
     * Cada punto lleva una información asociada.
     */
    map <Punto, InfoPunto> puntos;

    /**
     * Mapa de rutas del almacén.
     * Cada código tiene una ruta asociada.
     */
    map <Codigo, Ruta> rutas;

    /**
     * Lee una ruta, incluyendo en el almacén los puntos de la ruta.
     * Incluye la ruta en el almacén.
     * @param input Flujo de lectura.
     */
    void leeRuta (istream& input);

    /**
     * Lee una descripción, añadiéndola al punto.
     * Incluye la ruta en el almacén.
     * @param input Flujo de lectura.
     */
    void leeDescripcion (istream& input);
    
public:
    /**
     * Lee un almacén completo.
     * @param input Flujo de lectura del almacén.
     * @param almacen Almacén donde se leerá.
     */
    friend istream& operator >> (istream& input, Almacen& almacen);

    /**
     * Obtiene una ruta del almacén mediante su código.
     * @param codigo Código de la ruta.
     * @return Ruta con el código introducido.
     */
    inline Ruta obtenerRuta (Codigo codigo) {
    	return rutas[codigo];
    }

    /**
     * Obtiene la descripción de un punto del almacén.
     * @param punto Punto cuya descripción se busca.
     */
    inline Descripcion obtenerDescripcion (Punto punto) {
    	return puntos[punto].descripcion;
    }

    /**
     * Obtiene las rutas que pasan por un punto del almacén.
     * @param punto Punto cuyas rutas se buscan.
     */
    inline Rutas obtenerRutas (Punto punto) {
    	return puntos[punto].rutas;
    }



    /**
     * Iteradores para el almacén.
     */
    typedef map<Codigo,Ruta>::iterator iterator;

    /**
     * Inicio del almacén.
     */
    inline iterator begin () {
    	return rutas.begin();
    }

    /**
     * Final del almacén.
     */
    inline iterator end () {
    	return rutas.end();
    }
};


/**
 * Retira espacios, tabulaciones y saltos de línea de un flujo.
 * @param input Flujo de entrada.
 */
void retirarEspacios (istream& input);


/**
 * Escribe el contenido de una ruta.
 * @param output Flujo de salida de la ruta.
 * @param ruta Ruta que se escribirá.
 */
ostream& operator << (ostream& output, const Ruta& ruta);


#endif
