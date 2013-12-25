## VARIABLES GLOBALES

# Directorios
SRC = ./src
INCLUDE = ./include

# Archivos
EXE = ./bin/rutas
MAIN = $(SRC)/main.cpp
SOURCES = $(SRC)/almacen.cpp $(SRC)/punto.cpp
INCLUDES = $(INCLUDE)/almacen.h $(INCLUDE)/punto.h

# Compliación
CC = g++
FLAGS = -Wall --std=c++11 -I$(INCLUDE)


## COMPILACIÓN
$(EXE): $(MAIN) $(SOURCES)
	$(CC) $< $(SOURCES) -o $(EXE) $(FLAGS)

clean:
	rm -f $(EXE)
