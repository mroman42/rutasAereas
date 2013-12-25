#ifndef _ALMACEN_H
#define _ALMACEN_H

#include <string>
#include <iostream>
#include <list>
#include <map>
#include "punto.h"
#include "ruta.h"

typedef std::string Descripcion;
typedef std::string Codigo;
typedef std::list<Ruta*> Rutas;

/**
 * T.D.A. Almacén
 * Contiene todas las rutas sobre un mapa, así como los puntos
 * destacados del mismo, que formarán parte de las rutas.
 */
class Almacen {
private:
    std::map < Punto, std::pair<Descripcion, Rutas> > puntos;
    std::map < Codigo, Ruta > rutas;

    /**
     * Lee una ruta, incluyendo en el almacén los puntos de la ruta.
     * Incluye la ruta en el almacén.
     */
    void leeRuta (istream& input);

public:
    //friend istream& operator >> (istream& input, Almacen& almacen);

};


/**
 * Lee un almacén completo.
 * @param input Flujo de lectura del almacén.
 * @param almacen Almacén donde se leerá.
 */
// istream& operator >> (istream& input, Almacen& almacen) {
//     /**
//      * Un almacén tendrá el siguiente formato:
//      * 
//      * #Rutas
//      * <ruta1>
//      * <ruta2>
//      * ...
//      * #Puntos_de_Interes
//      * <latitud1,longitud1> <descripción1>
//      * <latitud2,longitud2> <descripción2>
//      * ...
//      */

//     // Vacía el anterior almacén.
//     almacen.rutas.clear();
//     almacen.puntos.clear();

//     // Lectura de rutas y de descripciones.
//     string cabecera;

//     // Rutas
//     if (input >> cabecera and cabecera == "#Rutas") {
// 	while (input.peek != '#')
// 	    leeRuta(input);
//     }

//     // Descripciones
//     if (input >> cabecera and cabecera == "#Puntos_de_Interes") {
// 	Punto actual;
// 	string descripcion_leida;

// 	while (input >> actual) {
// 	    input >> descripcion_leida;
// 	    mmi localizado = puntos.find(actual);
	        
// 	    if (!localizado)
// 		cerr << "ERROR, no se localizó el punto.";
// 	    else
// 		localizado->descripcion = descripcion_leida;
// 	}
//     }
// }

#endif
