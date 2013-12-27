#include "pais.h"

using namespace std;


istream& operator >> (istream& input, Pais& leido) {
    /**
     * El formato de un punto será:
     *    <latitud> <longitud> <nombre> <bandera>
     * Leemos cada una de las partes de la ruta. 
     */
    input >> leido.ubicacion.Latitud();
    input >> leido.ubicacion.Longitud();
    input >> leido.nombre;
    input >> leido.bandera;
    
    return input;
}
