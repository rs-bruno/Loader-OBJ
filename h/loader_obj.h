#ifndef __LOADER_OBJ__
#define __LOADER_OBJ__
#include <list>
#include <map>
using namespace std;

/*
	Representa un poligono que conforma una cara del modelo.
	El tamaño de los tres arreglos siempre es vertex_count.
	Un valor -1 en los arreglos ind_uvs o ind_normals significa que ese vértice no cuenta
	con información de uv o normal.
*/
typedef struct{
	int vertex_count;
	int* ind_vertices;
	int* ind_uvs;
	int* ind_normals;
} cara;

class ConjuntoCaras {
	public:
		ConjuntoCaras();
		~ConjuntoCaras();
		ConjuntoCaras(const ConjuntoCaras&) = default;
		ConjuntoCaras& operator=(const ConjuntoCaras&) = default;

		/*
			Inserta una cara al conjunto.
		*/
		void instestarCara(cara);
		
		/*
			Devuelve un arreglo con los índices del vector de listas que no son vacías.
			El arreglo siempre tiene tamaño al menos 1 y el primer elemento indica el tamaño del arreglo - 1,
			es decir la cantidad de listas no vacías.
		*/
		int* indicesListas();

		/*
			Devuelve la lista que tiene a las caras que son poligonos de ésa cantidad de vértices.
		*/
		list<cara>& devolverLista(int cant_vertices);
	
	private:
		/*
			La clave es la cantidad de vértices de las caras que almacena la lista asociada.
		*/
		map<int, list<cara>> listas;
};

typedef struct{
		/*
			Elementos básicos del modelo.
		*/
		int vertex_count;
		int uv_count;
		int normal_count;
		float* vertex_arr;
		float* uv_arr;
		float* normal_arr;
		
		/*
			Caras del modelo.
		*/
		ConjuntoCaras caras;
}modelo;

/*
	Devuelve un modelo, recibe como entrada la ruta del archivo.obj a cargar.
*/
modelo load_obj(char*);

/*
	Imprime una cara en la salida estándar.
*/
void print_cara(cara c);

/*
	Imprime un modelo en la salida estándar.
*/
void print_modelo(modelo m);
#endif