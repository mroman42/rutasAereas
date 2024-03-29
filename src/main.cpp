#include "almacen.h"
#include "paises.h"
#include "imagen.h"
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;


/**
 * Programa para mostrar el mapa sobre el que se señalizan las rutas.
 * Se invocará usando como argumentos:
 *   rutas  <datos de países> <mapa> <directorio de banderas> <almacén de rutas> <avión> <máscara> <ruta>
 * Mostrará por pantalla los datos de la ruta indicada y creará la imagen pedida en disco.
 * La imagen de salida tendrá como nombre: <ruta>.ppm.
 */
int main(int argc, char * argv[]){
    /**
     * Bloque de entradas.
     */
    typedef const string Mensaje;

    //Mensajes de error.
    const int NUM_ARGS = 8;
    Mensaje MSGARGS [] = {"Introduzca los siguientes argumentos:",
			  " 1. Fichero de datos de países.",
			  " 2. Mapa del mundo.",
			  " 3. Directorio de banderas.",
			  " 4. Almacén de rutas.",
			  " 5. Imagen del avión.",
			  " 6. Máscara del avión.",
			  " 7. Ruta a realizar."};
	
    
    // Lectura y comprobación de argumentos.
    if (argc != NUM_ARGS) {
        for (int i=0; i<NUM_ARGS; ++i)
            cerr << MSGARGS[i] << endl;
        return -1;
    }
    
    string ruta_elegida = argv[7];
    string dir_banderas = argv[3];

    // Apertura de los ficheros de entrada.
    ifstream archivo_paises (argv[1]);
    ifstream archivo_mapa (argv[2]);
    ifstream archivo_almacen (argv[4]);
    ifstream archivo_avion (argv[5]);
    ifstream archivo_mascara (argv[6]);

    if (!archivo_paises) {
        cerr << "Error al abrir el archivo " << argv[1] << endl;
        return -1;
    }
    if (!archivo_mapa) {
        cerr << "Error al abrir el archivo " << argv[2] << endl;
        return -1;
    }
    if (!archivo_almacen) {
        cerr << "Error al abrir el archivo " << argv[4] << endl;
        return -1;
    }
    if (!archivo_avion) {
        cerr << "Error al abrir el archivo " << argv[5] << endl;
        return -1;
    }
    if (!archivo_mascara) {
        cerr << "Error al abrir el archivo " << argv[6] << endl;
        return -1;
    }


    // Obtiene los países y su información del fichero indicado.
    Paises paises;
    archivo_paises >> paises;

    // Obtiene las rutas y puntos de interés del fichero indicado.
    Almacen almacen;
    archivo_almacen >> almacen;

    // Obtiene las imágenes de los ficheros indicados.
    Imagen mapa;
    Imagen avion;
    Imagen mascara;

    archivo_mapa >> mapa;   
    archivo_avion >> avion;
    archivo_mascara >> mascara;


    // Cerramos los archivos de entrada.
    archivo_paises.close();
    archivo_mapa.close();
    archivo_almacen.close();
    archivo_avion.close();
    archivo_mascara.close();


    /**
     * Bloque de cómputos.
     */
    // Obtenemos la ruta y mostramos la información más importante de ella.
    Ruta ruta = almacen.obtenerRuta(ruta_elegida);
    if (ruta.empty()) {
        cerr << "La ruta indicada no existe o está vacía.\n";
        exit(-1);
    }
    
    typedef Ruta::iterator rit;

    cout << "La ruta se escribe como: " << endl;
    cout << argv[7] << "\n" << ruta.size() << " países:\n";

    for (rit i = ruta.begin(); i != ruta.end(); ++i) {
        cout << paises[*i].nombre << " " << *i << endl;
    }
    
    // Recorrido de los países de la ruta.
    // Pegado de banderas y aviones.
    int total_columnas = mapa.numColumnas();
    int total_filas = mapa.numFilas();

    Imagen bandera;

    for (rit i = ruta.begin(); i != ruta.end(); ++i) {
        Pais& pais = paises[*i];
        int pos_filas = (total_filas/360.0) * (180 + i->Longitud()) + 15;
        int pos_columnas = (total_columnas/180.0) * (90 - i->Latitud()) + 20;

        // Pegado de bandera.
        ifstream archivo_bandera (dir_banderas + "/" + pais.bandera);
        if (!archivo_bandera) {
            cerr << "Error al abrir el archivo ";
            return -1;
        }

        Imagen bandera;
        archivo_bandera >> bandera;
        archivo_bandera.close();
        mapa.pega (bandera, VACIA, false, pos_filas - bandera.numFilas()/2, pos_columnas - bandera.numColumnas()/2);

        // Rotado del avión parado en el aeropuerto.
        Imagen avion_rotado = avion;
        Imagen mascara_rotada = mascara;

        rit siguiente = i;
        ++siguiente;

        if (siguiente == ruta.end())
            siguiente = ruta.begin();

        int sig_pos_filas = (total_filas/360.0) * (180 + siguiente->Longitud()) + 15;
        int sig_pos_columnas = (total_columnas/180.0) * (90 - siguiente->Latitud()) + 20;
        double angulo = atan2 (((double) (pos_columnas - sig_pos_columnas)), (sig_pos_filas - pos_filas));

        avion_rotado.rota (angulo);
        mascara_rotada.rota (angulo);

        // Cálculo de la posición del avión surcando los cielos.
        int med_pos_filas = (sig_pos_filas + pos_filas) / 2;
        int med_pos_columnas = (sig_pos_columnas + pos_columnas) / 2;

        // Pegado de los aviones.
        mapa.pega (avion_rotado, mascara_rotada, true, pos_filas - avion.numFilas()/2, pos_columnas - avion.numColumnas()/2);
        mapa.pega (avion_rotado, mascara_rotada, false, med_pos_filas - avion.numFilas()/2, med_pos_columnas - avion.numColumnas()/2);
    }

    //Creamos y abrimos el archivo de salida y grabamos la imagen en él.
    string archivo_salida = (string) ruta_elegida + ".ppm";
    fstream salida (archivo_salida, fstream::out);
    salida << mapa;
    salida.close();

    return 0;  
}
