#include <iostream>
#include "../h/loader_obj.h"
using namespace std;

int main(int argc, char* argv[]){
	char path[] = "456.obj";
	modelo m = load_obj(path);
	print_modelo(m);
	cout << "Saliendo" << endl;
	return 0;
}