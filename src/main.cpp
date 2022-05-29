#include <iostream>
#include "../h/loader_obj.h"
using namespace std;

int main(int argc, char* argv[]){
	char path[] = "models/456.obj";
	modelo m = load_modelo(path);
	print_modelo(m);
	free_modelo(m);
	return 0;
}