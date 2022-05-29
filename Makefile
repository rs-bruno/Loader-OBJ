# Directorios
HEADERS = h
SOURCE = src
OBJECTS = o
SCRIPTS = py

all: main.exe

$(OBJECTS)/loader_obj.o: $(SOURCE)/loader_obj.cpp $(HEADERS)/loader_obj.h
	g++ -c $< -o $@

main.exe: $(SOURCE)/main.cpp $(OBJECTS)/loader_obj.o
	g++ -o main.exe $^

clean:
	py $(SCRIPTS)/clean.py