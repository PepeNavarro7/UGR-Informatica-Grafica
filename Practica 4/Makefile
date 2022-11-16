.PHONY: all do clean

CC := g++ # El compilador
CPPFLAGS := -Wall -fmax-errors=2 -g  # Los flags del compilador
LIBS := -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331 # Librerias

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include
BIN_DIR := bin

TARGET := $(BIN_DIR)/ejecutable #Ejecutable
SRC := $(wildcard $(SRC_DIR)/*.cc) # Archivos source
OBJ := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC)) # Archivos .o
DEPS := $(wildcard $(INC_DIR)/*.*) # Includes


all: $(TARGET)

$(TARGET): directorios $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBS) 

directorios:
	@mkdir -p obj
	@mkdir -p bin

$(OBJ_DIR)/jirafa.o: $(SRC_DIR)/jirafa.cc $(DEPS)
	$(CC) $(CPPFLAGS) -c $< -o $@
$(OBJ_DIR)/objetos_B3.o: $(SRC_DIR)/objetos_B3.cc $(DEPS)
	$(CC) $(CPPFLAGS) -c $< -o $@
$(OBJ_DIR)/file_ply_stl.o: $(SRC_DIR)/file_ply_stl.cc $(DEPS)
	$(CC) $(CPPFLAGS) -c $< -o $@
$(OBJ_DIR)/practica_objetos_B3.o: $(SRC_DIR)/practica_objetos_B3.cc $(DEPS)
	$(CC) $(CPPFLAGS) -c $< -o $@

do: $(TARGET)
	./$(TARGET) txt/beethoven

clean:
	rm -rf $(OBJ) $(TARGET)