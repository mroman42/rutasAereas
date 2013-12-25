#include "almacen.h"

using namespace std;

void Almacen::leeRuta (istream& input) {
    /**
     * El formato de una ruta será:
     *    <codigo> <numero_puntos> <punto1> ...
     * Leemos cada una de las partes de la ruta. 
     */

    // Lee código y tamaño.
    Codigo codigo;
    int tamanio;
    input >> codigo;
    input >> tamanio;

    // Trabajamos con la ruta dada por el código
    Ruta& actual = rutas[codigo];

    // Lee los nuevos puntos y los inserta.
    for (int i=0; i<tamanio; ++i) {
	Punto leido;
	input >> leido;

	actual.push_back(leido);
	puntos[leido].rutas.push_back(&actual);
    }
}


void Almacen::leeDescripcion (istream& input) {
    /**
     * El formato de una descripción será:
     *  <punto> <descripción>
     */
    Punto punto_leido;
    Descripcion descripcion_leida;

    // Lee en cada línea un punto y asigna descripción.
    if (input >> punto_leido) {
	getline(input, descripcion_leida);
	puntos[punto_leido].descripcion = descripcion_leida;
    }
}



istream& operator >> (istream& input, Almacen& almacen) {
    /**
     * El formato del almacén será:
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

    // Lectura de rutas y de descripciones.
    string cabecera;

    // Rutas
    if (input >> cabecera and cabecera == "#Rutas") {
	while (input.peek() != '#')
	    leeRuta(input);
    }

    // Descripciones
    if (input >> cabecera and cabecera == "#Puntos_de_Interes")
	while (input.peek())
	    leeDescripcion(input);
	
}
