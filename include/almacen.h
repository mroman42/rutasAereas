#ifndef _ALMACEN_H
#define _ALMACEN_H

#include <string>
#include <iostream>
#include <list>
#include <map>
#include "punto.h"

typedef std::string Descripcion;
typedef std::string Codigo;
typedef std::list<Punto> Ruta;
typedef std::list<Codigo> Rutas;


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
	Descripcion descripcion;
	Rutas rutas;
    };

    /**
     * Mapa de puntos del almacén.
     * Cada punto lleva una información asociada.
     */
    std::map <Punto, InfoPunto> puntos;

    /**
     * Mapa de rutas del almacén.
     * Cada código tiene una ruta asociada.
     */
    std::map <Codigo, Ruta> rutas;

    /**
     * Lee una ruta, incluyendo en el almacén los puntos de la ruta.
     * Incluye la ruta en el almacén.
     */
    void leeRuta (istream& input);

    /**
     * Lee una descripción, añadiéndola al punto.
     * Incluye la ruta en el almacén.
     */
    void leeDescripcion (istream& input);
    
public:
    /**
     * Lee un almacén completo.
     * @param input Flujo de lectura del almacén.
     * @param almacen Almacén donde se leerá.
     */
    friend std::istream& operator >> (std::istream& input, Almacen& almacen);

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
    typedef std::map<Codigo,Ruta>::iterator iterator;

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
std::ostream& operator << (std::ostream& output, const Ruta& ruta);


#endif
