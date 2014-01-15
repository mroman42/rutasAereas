#ifndef _PAISES_H
#define _PAISES_H

#include <string>
#include <iostream>
#include <list>
#include "punto.h"
#include <map>

using std::map;
using std::string;

/**
 * El struct Pais contiene la información de un pais del conjunto
 */
struct Pais {
    /**
     * Nombre del país y ruta de la imagen a la bandera del país.
     */
    string nombre;
    string bandera;

    /**
     * Constructor del pais.
     */
};


/**
 * T.D.A. Paises
 * Contiene todos los países sobre un mapa, así como la 
 * información asociada.
 */
class Paises {
private:
    /**
     * Mapa de países.
     * Cada país se localiza por su ubicación.
     */
    map <Punto, Pais> paises;
    
public:
    /**
     * Obtiene la información de dicho país.
     * @param ubicacion Ubicación del país.
     * @return Pais en la posición introducida.
     */
    inline Pais obtenerPais (Punto ubicacion) {
    	return paises[ubicacion];
    }

    /**
     * Iteradores para los países.
     */
    typedef map<Punto,Pais>::iterator iterator;

    /**
     * Inicio de los países.
     */
    inline iterator begin () {
    	return paises.begin();
    }

    /**
     * Final de los países.
     */
    inline iterator end () {
    	return paises.end();
    }

    /**
     * Lee el conjunto de países.
     * @param input Flujo de lectura.
     * @param paises Conjunto de países contenidos.
     */
    friend std::istream& operator >> (std::istream& input, Paises& conjunto);

    /**
     * Imprime todos los países.
     * @param output Flujo de salida.
     * @param conjunto Conjunto que se imprimirá.
     */
    friend std::ostream& operator << (std::ostream& output, Paises& conjunto);

};
#endif
