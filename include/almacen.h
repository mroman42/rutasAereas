#ifndef _ALMACEN_H
#define _ALMACEN_H

#include <list>
#include <multimap>

/**
 * T.D.A. Almacén
 * Contiene todas las rutas sobre un mapa, así como los puntos
 * destacados del mismo, que formarán parte de las rutas.
 */
class Almacen {
private:
    list<Ruta> rutas;
    multimap<Punto,Ruta> puntos;

public:
    
};

#endif
