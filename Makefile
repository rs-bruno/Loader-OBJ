# Directorios
H = h
OBJ = obj
SRC = src
SCRIPTS = py

all: main.exe

$(OBJ)/loader_obj.o: $(SRC)/loader_obj.cpp $(H)/loader_obj.h
	g++ -c $< -o $@

main.exe: $(SRC)/main.cpp $(OBJ)/loader_obj.o
	g++ -o main.exe $^

clean:
	py $(SCRIPTS)/clean.py