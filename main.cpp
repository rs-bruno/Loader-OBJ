#include "loader_obj.h"

int main(int argc, char* argv[]){
	char path[] = "cubo1.obj";
	modelo m = load_obj(path);
	print_modelo(m);
}