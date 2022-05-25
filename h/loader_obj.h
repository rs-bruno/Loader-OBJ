#ifndef __LOADER_OBJ__
#define __LOADER_OBJ__
typedef struct{
	int vertex_count;
	int uv_count;
	int normal_count;
	int index_count;
	float* vertex_arr;
	float* uv_arr;
	float* normal_arr;
	int* index_arr;
} modelo;

//Devuelve un modelo, recibe como entrada la ruta del archivo.obj a cargar.
modelo load_obj(char*);
//Imprime un modelo en la salida estándar.
void print_modelo(modelo m);
#endif