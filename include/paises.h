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
    Pais(string name="Unknow", string flag="unknow")
    : nombre(name), bandera(flag)
    {}
};


/**
 * T.D.A. Paises
 * Mapa de países ordenados por ubicación
 */
class Paises : public map <Punto, Pais> {    
public:
    /**
     * Obtiene la información de dicho país.
     * @param ubicacion Ubicación del país.
     * @return Pais en la posición introducida.
     */
    inline Pais obtenerPais (Punto ubicacion) {
    	return operator[](ubicacion);
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
