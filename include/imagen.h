#ifndef _IMAGEN_H
#define _IMAGEN_H

#include <iostream>
#include <limits>

/**
 * Pixel de una imagen.
 * Contiene información del color del pixel y transparencia.
 */
struct Pixel {
    /**
     * Color del pixel.
     */
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    /**
     * Transparencia del pixel.
     */
    unsigned char transparencia;
};


/**
 * TDA Imagen.
 * Matriz de pixeles.
 */
class Imagen : public vector < vector<Pixel> > {
private:
    /**
     * @brief Tipo de imagen
     *
     * Declara una serie de constantes para representar los distintos tipos
     * de imágenes que se pueden manejar.
     *
     * @see LeerTipoImagen
     */
    enum TipoImagen {
	DESCONOCIDA,
	IMAGEN_PGM,
	IMAGEN_PPM
    };


    /**
     * Buffer con información en bruto de la imagen.
     * Información no interpretada de la imagen.
     */
    typedef unsigned char* Buffer;


    /**
     * Tamaño máximo permitido a una imagen.
     * Máximo de filas y máximo de columnas.
     */
    static const int TAMANIO_MAXIMO = 5000;

    
    /**
     * @brief Consulta el tipo de imagen del archivo y sus dimensiones
     *
     * @param input Flujo de entrada de datos.
     * @return Devuelve el tipo de la imagen en el archivo
     *
     * @see TipoImagen
     */
    static TipoImagen leerTipoImagen (istream& input);


    /**
     * @brief Lee la cabecera de una imagen PPM o PGM.
     * @param input Flujo de entrada de la imagen.
     * @param filas Número de filas de la imagen según la cabecera.
     * @param columnas Número de columnas de la imagen según la cabecera.
     * @return Verdadero si la lectura tuvo éxito.
     */
    static bool LeerCabecera (istream& input, int& filas, int& columnas)

    /**
     * @brief Lee una imagen de tipo PPM reservando la memoria necesaria.
     *
     * @param input Flujo de entrada de la imagen.
     * @param filas Parámetro de salida con las filas de la imagen.
     * @param columnas Parámetro de salida con las columnas de la imagen.
     * @return Buffer con la imagen en bruto. 
     * El buffer será una zona de memoria para obtener el valor de cada uno de los píxeles
     * como tripletas consecutivas en formato RGB (RGBRGBRGB...) por filas
     * desde la esquina superior izquierda a la inferior derecha.
     */
    static Buffer leerImagenPPM (istream& input, int& filas, int& columnas);
    
    /**
     * @brief Lee una imagen de tipo PGM reservando la memoria necesaria.
     *
     * @param input Flujo de entrada de la imagen.
     * @param filas Parámetro de salida con las filas de la imagen.
     * @param columnas Parámetro de salida con las columnas de la imagen.
     * @return Buffer con la imagen en bruto. 
     * El buffer será una zona de memoria para obtener el valor de cada uno de los píxeles
     * como un valor de grises por filas desde la esquina superior izquierda a la inferior derecha.
     */
    static Buffer leerImagenPGM (istream& input, int& filas, int& columnas);


    /**
     * Salta las líneas de comentarios del flujo de entrada.
     * Retirará las líneas que comiencen por # hasta encontrar una que no lo haga.
     * @param input Flujo de entrada.
     */
    static void saltarComentarios (istream& input)

    /**
     * Salta los separadores del flujo de entrada.
     * Retirará separadores del flujo hasta encontrar un caracter no separador.
     * @param input Flujo de entrada de los caracteres.
     * @return Caracter no separador.
     */
    static char saltarSeparadores (istream& input);
    

public:
    friend istream& operator >> (istream& input, Imagen& leida);
};

#endif
