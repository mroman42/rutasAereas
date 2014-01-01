## VARIABLES GLOBALES

# Directorios
SRC = ./src
INCLUDE = ./include

# Archivos
EXE = ./bin/rutas
MAIN = $(SRC)/main.cpp
SOURCES = $(SRC)/almacen.cpp $(SRC)/punto.cpp $(SRC)/pais.cpp $(SRC)/paises.cpp $(SRC)/imagen.cpp
INCLUDES = $(INCLUDE)/almacen.h $(INCLUDE)/punto.h $(INCLUDE)/pais.h $(INCLUDE)/paises.h $(INCLUDE)/imagen.h


# Compliación
CC = g++
CFLAGS = -Wall --std=c++11 -I$(INCLUDE)


## COMPILACIÓN
$(EXE): $(MAIN) $(SOURCES)
	$(CC) $< $(SOURCES) -o $(EXE) $(CFLAGS)

clean:
	rm -f $(EXE)
