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
        input >> leido.ubicacion.Latitud();
        input >> leido.ubicacion.Longitud();
        input >> leido.nombre;
        input >> leido.bandera;
        conjunto.paises[leido.ubicacion] = leido;
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

    Pais pais;

    for (Paises::iterator it = conjunto.begin(); it != conjunto.end(); ++it) {
	    pais = it->second;

        cout << pais.nombre << ": Está en " << pais.ubicacion << " y su bandera está en " << pais.bandera << "\n";
    }

    return output;
}
