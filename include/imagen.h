/**
 * Práctica: Rutas Aéreas
 * Asignatura: Estructura de Datos(2º DGIIM)
 * Autores: Óscar Bermúdez Garrido y Mario Román García
 */
#ifndef _IMAGEN_H
#define _IMAGEN_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
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
class Imagen : public std::vector< std::vector<Pixel> > {
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
     * Tipo de la imagen actual.
     */
    TipoImagen tipo;


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
    static TipoImagen leerTipoImagen (std::istream& input);


    /**
     * @brief Lee la cabecera de una imagen PPM o PGM.
     * @param input Flujo de entrada de la imagen.
     * @param filas Número de filas de la imagen según la cabecera.
     * @param columnas Número de columnas de la imagen según la cabecera.
     * @return Verdadero si la lectura tuvo éxito.
     */
    static bool LeerCabecera (std::istream& input, int& filas, int& columnas);

    /**
     * Salta las líneas de comentarios del flujo de entrada.
     * Retirará las líneas que comiencen por # hasta encontrar una que no lo haga.
     * @param input Flujo de entrada.
     */
    static void saltarComentarios (std::istream& input);

    /**
     * Salta los separadores del flujo de entrada.
     * Retirará separadores del flujo hasta encontrar un caracter no separador.
     * @param input Flujo de entrada de los caracteres.
     * @return Caracter no separador.
     */
    static char saltarSeparadores (std::istream& input);
    

public:
    /**
     * Constructor de una imagen dadas unas dimensiones.
     * @param filas Filas de la imagen.
     * @param columnas Columnas de la imagen.
     */
    Imagen (int filas = 0, int columnas = 0) 
	: std::vector < std::vector<Pixel> >(filas, std::vector<Pixel>(columnas))
	{}


    /**
     * @brief Obtiene una nueva imagen que es la versión rotada de la imagen.
     * @param angulo Ángulo a rotar la imagen de entrada. Debe estar en radianes.
     * @return Una nueva imagen que es la versión rotada de la original.
     * @pos La imagen queda rotada según el ángulo indicado.
     **/
    void rota (double angulo);

    /**
     * @brief Pega una nueva imagen sobre esta imagen, que se toma como fondo.
     * @param imagen Imagen que se pegará.
     * @param mascara Máscara de pegado de la imagen.
     * @param transparente Verdadero si se usará transparencia en el pegado y Falso si debe ser opaco.
     * @param offset_horizontal Desplazamiento horizontal del origen del pegado.
     * @param offset_vertical Desplazamiento vertical del origen del pegado.
     */
    void pega (const Imagen& imagen, const Imagen& mascara, const bool transparente, const int offset_x, const int offset_y);

    /**
     * Número de filas de la imagen.
     * @return Filas de la imagen.
     */
    inline int numFilas () const {
	return size();
    }

    /**
     * Número de columnas de la imagen.
     * @return Columnas de la imagen.
     */
    inline int numColumnas () const {
	return at(0).size();
    }

    /**
     * Lee una imagen completa.
     * @param input Flujo de lectura.
     * @param leida Imagen donde se guardará.
     */
    friend std::istream& operator >> (std::istream& input, Imagen& leida);

    /**
     * Imprime esta imagen.
     * @param output Flujo de salida.
     * @param leida Imagen que se escribirá.
     */
    friend std::ostream& operator << (std::ostream& output, const Imagen& leida);
};

const Imagen VACIA (0,0);


#endif
