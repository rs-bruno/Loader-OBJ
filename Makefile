all: main.exe

loader_obj.o: loader_obj.cpp
	g++ -c loader_obj.cpp

main.o: main.cpp
	g++ -c main.cpp

main.exe: main.o loader_obj.o
	g++ -o main.exe main.o loader_obj.o