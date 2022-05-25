# Directorios
H = h
OBJ = obj
SRC = src
SCRIPTS = py

all: main.exe

$(OBJ)/loader_obj.o: $(SRC)/loader_obj.cpp
	g++ -c $< -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -c $< -o $@

main.exe: $(OBJ)/main.o $(OBJ)/loader_obj.o
	g++ -o main.exe $?

clean:
	py $(SCRIPTS)/clean.py