#include "paises.h"

using namespace std;


istream& operator >> (istream& input, Paises& conjunto) {
    /**
     * El formato del almacén será:
     * # Latitud    Longitud    Pais    Bandera
     * <Latitud1> <Longitud1>  <Pais1> <Bandera1>
     * <Latitud2> <Longitud2>  <Pais2> <Bandera2>
     * ...
     */
    Pais leido;

    // Vamos hasta #Latitud 
    while (input.peek() != '#' and input)
	    retirarEspacios(input);

    // Nos saltamos la primera línea ya que no tiene datos
    while (input.peek() != '\n' and input)
	    input.get();

    while(input){
        input >> leido;
        conjunto.paises[leido.Nombre()] = leido;
        retirarEspacios(input);
    }

    return input;
}

ostream& operator << (ostream& output, Paises& conjunto) {
    /*
     * El formato será:
     * Los países son:
     *    <Pais1>
     *    <Pais2>
     *    <Pais3>
     *    ...
     */
    output << "Los países son: \n";

    for (Paises::iterator it = conjunto.begin(); it != conjunto.end(); ++it) {
	    output << it->second;
    }

    return output;
}
