#ifndef _IMAGEN_H
#define _IMAGEN_H


class Imagen {
private:
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
     * Número de filas de la imagen.
     */
    int filas;

    /**
     * Número de columnas de la imagen.
     */
    int columnas;

    
    /**
     * @brief Tipo de imagen.
     * Declara constantes para representar los distintos tipos de imágenes.
     */
    enum TipoImagen {
	DESCONOCIDO, // Tipo desconocido de imagen.
	IMAGEN_PGM,  // Tipo PGM de imagen.
	IMAGEN_PPM   // Tipo PPM de imagen.
    }

public:
};

#endif
