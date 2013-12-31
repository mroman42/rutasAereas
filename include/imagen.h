#ifndef _IMAGEN_H
#define _IMAGEN_H

/**
 * Pixel de una imagen.
 * Contiene información del color del pixel y transparencia.
 */
struct Pixel {
    /**
     * Color del pixel.
     */
    unsigned char r,g,b;

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
     * @brief Consulta el tipo de imagen del archivo y sus dimensiones
     *
     * @param input Flujo de entrada de datos.
     * @return Devuelve el tipo de la imagen en el archivo
     *
     * @see TipoImagen
     */
    static TipoImagen leerTipoImagen (istream& input);

public:
    friend istream& operator >> (istream& input, Imagen& leida);
};

#endif
