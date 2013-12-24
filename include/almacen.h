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
    map<string,Ruta> rutas;
    multimap<Punto,Ruta> puntos;

    


public:
    /**
     * Añade una ruta al almacén de rutas.
     * @param ruta Ruta a añadir.
     */
    void insertar_ruta (const Ruta& nueva_ruta) {
	rutas.insert(nueva_ruta);
    }
   
    /**
     * 
     */
 
};

#endif
