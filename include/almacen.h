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
typedef std::list<Ruta*> Rutas;

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
    std::map < Punto, InfoPunto > puntos;

    /**
     * Mapa de rutas del almacén.
     * Cada código tiene una ruta asociada.
     */
    std::map < Codigo, Ruta > rutas;

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
};




#endif
