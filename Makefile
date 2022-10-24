# Compilador C++
CC=g++

# Flags del Compilador (-g, -std=c++11, -Wall, -Wextra)
CFLAGS=-g

# ESTRUCTURA CLÁSICA EN UN PROYECTO C++
# -Proyecto
#  |-bin       (Ejecutables)
#  |-build     (Ficheros Objeto)
#  |-include   (Cabeceras)
#  |-lib       (Librerías)
#  |-src       (Código Fuente)
#  |-tmp       (Ficheros Temporales)

# Directorio de los ejecutables
BIN_DIR=bin
# Directorio de los ficheros objeto (.o)
OBJECTS_DIR=bin
# Directorio del código fuente (.cpp)
SRC_DIR=src
# Directorio de las cabeceras (.hpp)
INCLUDE_DIR=include

# Aquí poner todos los .cpp de tu proyecto cambiando el formato por .o
_OBJ = main.o matrix_utility.o neighbours.o 
OBJ = $(patsubst %,$(OBJECTS_DIR)/%,$(_OBJ))

# Nombre del Ejecutable
BIN_NAME = Clientee

# Target all (lo que se ejecuta cuando haces make)
all: Clientee

Clientee: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_NAME) $^

$(OBJECTS_DIR)/main.o: $(SRC_DIR)/main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJECTS_DIR)/matrix_utility.o: $(SRC_DIR)/matrix_utility.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJECTS_DIR)/neighbours.o: $(SRC_DIR)/neighbours.cc
	$(CC) $(CFLAGS) -c -o $@ $<

# Ejecuta el programa
.PHONY: run
run: 
	@./$(BIN_DIR)/$(BIN_NAME)

# Limpia el directorio del proyecto (Borra ejecutables y ficheros objeto)
.PHONY: clean
clean:
	@rm -rf $(BIN_DIR)/* $(OBJECTS_DIR)/*