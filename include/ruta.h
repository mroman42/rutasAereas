#ifndef _RUTA_H
#define _RUTA_H

#include <string>
#include <list>


/**
 * T.D.A. Ruta
 * Contiene la información referente a toda una ruta de puntos.
 * 
 */
class Ruta {
private:
    /**
     * Puntos que contiene la ruta.
     */
    list<Punto*> puntos;

    /**
     * 
     */
    string codigo;

public:
    
    friend istream& operator >> (istream& input, Ruta& leida); 
};




/**
 * Lee una ruta, guardando su información en la ruta indicada.
 * @param input Flujo de lectura de la ruta.
 * @param leida Ruta sobre la que se escribirá.
 */
istream& operator >> (istream& input, Ruta& leida) {
    /**
     * El formato de una ruta será:
     *    <codigo> <numero_puntos> <punto1> ...
     * Leemos cada una de las partes de la ruta. 
     */

    // Lee código y tamaño.
    int tamanio;
    input >> leida.codigo;
    input >> tamanio;

    // Lee puntos de la nueva ruta.
    leida.puntos.clear();
    for (int i=0; i<tamanio; ++i) {
	    Punto nuevo_punto;
	    input >> nuevo_punto;
	    leida.puntos.insert(nuevo_punto);
    }
}


#endif
