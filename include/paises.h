#ifndef _PAISES_H
#define _PAISES_H

#include <string>
#include <iostream>
#include <list>
#include "pais.h"
#include <map>

using std::map;

typedef std::string Nombre;


/**
 * T.D.A. Paises
 * Contiene todos los países sobre un mapa, así como la 
 * información asociada.
 */
class Paises {
private:
    /**
     * Mapa de países.
     * Cada país se localiza por su nombre.
     */
    map <Nombre, Pais> paises;
    
public:
    /**
     * Obtiene la información de dicho país.
     * @param nombre Nombre del país.
     * @return Pais con el nombre introducido.
     */
    inline Pais obtenerPais (Nombre nombre) {
    	return paises[nombre];
    }

    /**
     * Iteradores para los países.
     */
    typedef map<Nombre,Pais>::iterator iterator;

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
    friend std::istream& operator >> (std::istream& input, Paises& paises);

    /**
     * Imprime todos los países.
     * @param output Flujo de salida.
     * @param conjunto Conjunto que se imprimirá.
     */
    friend std::ostream& operator << (std::ostream& output, Paises& conjunto);

};
#endif
