## VARIABLES GLOBALES

# Directorios
SRC = ./src
INCLUDE = ./include

# Archivos
EXE = ./bin/rutas
ROTA = ./bin/rota
PEGA = ./bin/pega
MAIN = $(SRC)/main.cpp
SOURCES = $(SRC)/almacen.cpp $(SRC)/punto.cpp $(SRC)/pais.cpp $(SRC)/paises.cpp $(SRC)/imagen.cpp
INCLUDES = $(INCLUDE)/almacen.h $(INCLUDE)/punto.h $(INCLUDE)/pais.h $(INCLUDE)/paises.h $(INCLUDE)/imagen.h


# Compliación
CC = g++
CFLAGS = -Wall --std=c++11 -I$(INCLUDE)



## COMPILACIÓN
all: $(EXE) $(ROTA) $(PEGA)

$(EXE): $(MAIN) $(SOURCES)
	$(CC) $< $(SOURCES) -o $(EXE) $(CFLAGS)

$(ROTA): $(SRC)/rota.cpp $(SRC)/imagen.cpp
	$(CC) $< $(SRC)/imagen.cpp -o $@ $(CFLAGS)

$(PEGA): $(SRC)/pega.cpp $(SRC)/imagen.cpp
	$(CC) $< $(SRC)/imagen.cpp -o $@ $(CFLAGS)

clean:
	rm -f $(EXE)
	rm -f $(ROTA)
	rm -f $(PEGA)
