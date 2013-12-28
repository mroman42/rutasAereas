#include "pais.h"

using namespace std;


istream& operator >> (istream& input, Pais& leido) {
    /**
     * El formato de un punto será:
     *    <latitud> <longitud> <nombre> <bandera> 
     */
    input >> leido.ubicacion.Latitud();
    input >> leido.ubicacion.Longitud();
    input >> leido.nombre;
    input >> leido.bandera;
    
    return input;
}

ostream& operator << (ostream& output, Pais& pais) {
    /*
     * El formato será:
     *    <nombre>: Está en <punto> y su bandera está en <bandera> 
     */
    output << pais.nombre << ": Está en " << pais.ubicacion << " y su bandera está en " << pais.bandera << "\n";

    return output;
}
