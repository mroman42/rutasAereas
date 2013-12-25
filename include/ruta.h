#ifndef _RUTA_H
#define _RUTA_H

#include <string>
#include <list>
#include "punto.h"

using std::string;
using std::list;

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
    list<Punto> puntos;

public:
    friend class Almacen;
};
#endif
