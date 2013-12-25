#ifndef _ALMACEN_H
#define _ALMACEN_H

#include <list>
#include <multimap>

typedef std::multimap<Punto,Ruta>::iterator mmi;


/**
 * T.D.A. Almacén
 * Contiene todas las rutas sobre un mapa, así como los puntos
 * destacados del mismo, que formarán parte de las rutas.
 */
class Almacen {
private:
    std::map<string,Ruta> rutas;
    std::multimap<Punto,Ruta> puntos;


    /**
     * Inserta una ruta en el almacén.
     * Se suponen sus puntos ya insertados en el almacén.
     */
    inline void insertaRuta (const Ruta& ruta) {
	    rutas.insert(std::pair<string,Ruta>(ruta.codigo, ruta));
    }


    /**
     * Lee una ruta, incluyendo en el almacén los puntos de la ruta.
     * Incluye la ruta en el almacén.
     */
    void leeRuta (istream& input) {
        /**
	     * El formato de una ruta será:
	     *    <codigo> <numero_puntos> <punto1> ...
	     * Leemos cada una de las partes de la ruta. 
	     */
	
	    Ruta leida;

	    // Lee código y tamaño.
	    int tamanio;
	    input >> leida.codigo;
	    input >> tamanio;

	    // Lee puntos de la nueva ruta.
	    // Inserta los puntos en el almacén.
	    leida.puntos.clear();
	    for (int i=0; i<tamanio; ++i) {
	        Punto nuevo_punto;
	        input >> nuevo_punto;

	        mmi insertado = puntos.insert(std::pair<Punto,Ruta>(nuevo_punto, leida));
	        leida.puntos.insert(insertado);
	    }

	    // Inserta la ruta en el almacén. 
	    insertaRuta(leida);
    }

public:
    friend istream& operator >> (istream& input, Almacen& almacen);
};


/**
 * Lee un almacén completo.
 */
istream& operator >> (istream& input, Almacen& almacen) {
    /**
     * Un almacén tendrá el siguiente formato:
     * 
     * #Rutas
     * <ruta1>
     * <ruta2>
     * ...
     * #Puntos_de_Interes
     * <latitud1,longitud1> <descripción1>
     * <latitud2,longitud2> <descripción2>
     * ...
     */

    // Vacía el anterior almacén.
    almacen.rutas.clear();
    almacen.puntos.clear();

    // Lectura de rutas y de descripciones.
    string cabecera;

    // Rutas
    if (input >> cabecera and cabecera == "#Rutas") {
	    while (input.peek != '#')
	        leeRuta(input);
    }

    // Descripciones
    if (input >> cabecera and cabecera == "#Puntos_de_Interes") {
	    Punto actual;
	    string descripcion_leida;

	    while (input >> actual) {
	        input >> descripcion_leida;        
	    }
    }
}

#endif
