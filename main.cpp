#include <cstdio>
#include <iostream>
#include <list>
#include <regex>
#include <string>
using namespace std;

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

modelo load_obj(char* path){
	modelo ret;
	FILE* model_file = fopen(path, "r");
	list<float> l_vertices;
	list<float> l_uvs;
	list<float> l_normals;
	list<int> ind_vertices;
	list<int> ind_uvs;
	list<int> ind_normals;

	list<char*> lines;
	char buff[128];
	while (fgets(buff, sizeof(buff), model_file)) {
		char* nl = new char[strlen(buff)];
		strcpy(nl, buff);
		lines.push_back(nl);
	}
	fclose(model_file);
	regex re1("v ([-]?[0-9]*\\.[0-9]*) ([-]?[0-9]*\\.[0-9]*) ([-]?[0-9]*\\.[0-9]*)");
	regex re2("vt ([-]?[0-9]*\\.[0-9]*) ([-]?[0-9]*\\.[0-9]*)");
	regex re3("vn ([-]?[0-9]*\\.[0-9]*) ([-]?[0-9]*\\.[0-9]*) ([-]?[0-9]*\\.[0-9]*)");
	regex re4("f ([0-9]*)/([0-9]*)/([0-9]*) ([0-9]*)/([0-9]*)/([0-9]*) ([0-9]*)/([0-9]*)/([0-9]*)");
	cmatch m;
	for(list<char*>::iterator it = lines.begin(); it != lines.end(); ++it){
		if(regex_search(*it, m, re1)){
			l_vertices.push_back(stof(m[1].str()));
			l_vertices.push_back(stof(m[2].str()));
			l_vertices.push_back(stof(m[3].str()));
		}
	}
	for(list<char*>::iterator it = lines.begin(); it != lines.end(); ++it){
		if(regex_search(*it, m, re2)){
			l_uvs.push_back(stof(m[1].str()));
			l_uvs.push_back(stof(m[2].str()));
		}
	}
	for(list<char*>::iterator it = lines.begin(); it != lines.end(); ++it){
		if(regex_search(*it, m, re3)){
			l_normals.push_back(stof(m[1].str()));
			l_normals.push_back(stof(m[2].str()));
			l_normals.push_back(stof(m[3].str()));
		}
	}
	for(list<char*>::iterator it = lines.begin(); it != lines.end(); ++it){
		if(regex_search(*it, m, re4)){
			ind_vertices.push_back(stoi(m[1].str()) - 1);
			ind_vertices.push_back(stoi(m[4].str()) - 1);
			ind_vertices.push_back(stoi(m[7].str()) - 1);
			ind_uvs.push_back(stoi(m[2].str()) - 1);
			ind_uvs.push_back(stoi(m[5].str()) - 1);
			ind_uvs.push_back(stoi(m[8].str()) - 1);
			ind_normals.push_back(stoi(m[3].str()) - 1);
			ind_normals.push_back(stoi(m[6].str()) - 1);
			ind_normals.push_back(stoi(m[9].str()) - 1);
		}
	}

	ret.vertex_count = l_vertices.size() / 3;
	ret.vertex_arr = new float[l_vertices.size()];
	list<float>::iterator it = l_vertices.begin();
	for(int i = 0; i < l_vertices.size(); ++i)
		ret.vertex_arr[i] = *(it++);

	float* uvs_aux = new float[l_uvs.size()];
	it = l_uvs.begin();
	for(int i = 0; i < l_uvs.size(); ++i)
		uvs_aux[i] = *(it++);
	ret.uv_arr = new float[ind_uvs.size()*2];
	int i = 0;
	for(list<int>::iterator it = ind_uvs.begin(); it != ind_uvs.end(); ++it){
		ret.uv_arr[2*i] = uvs_aux[2*(*it)];
		ret.uv_arr[2*i+1] = uvs_aux[2*(*it)+1];
		++i;
	}
 	ret.uv_count = ind_uvs.size();

	float* normals_aux = new float[l_normals.size()];
	it = l_normals.begin();
	for(int i = 0; i < l_normals.size(); ++i)
		normals_aux[i] = *(it++);
	ret.normal_arr = new float[ind_normals.size()*3];
	i = 0;
	for(list<int>::iterator it = ind_normals.begin(); it != ind_normals.end(); ++it){
		ret.normal_arr[3*i] = normals_aux[3*(*it)];
		ret.normal_arr[3*i+1] = normals_aux[3*(*it)+1];
		ret.normal_arr[3*i+2] = normals_aux[3*(*it)+2];
		++i;
	}

	ret.normal_count = ind_normals.size();

	ret.index_arr = new int[ind_vertices.size()];
	i = 0;

	for(list<int>::iterator it = ind_vertices.begin(); it != ind_vertices.end(); ++it){
		ret.index_arr[i++] = *it;
	}

	ret.index_count = ind_vertices.size();
	delete[] uvs_aux;
	delete[] normals_aux;
	return  ret;
}

void print_modelo(modelo m){
	cout << "vertex_arr:" << "(" << m.vertex_count << ")" << endl;
	for(int i = 0; i < m.vertex_count; ++i){
		cout << i << ": (" << m.vertex_arr[3*i] << ", " << m.vertex_arr[3*i+1] << ", " << m.vertex_arr[3*i+2] << ") " << endl;
	}
	cout << endl;
	cout << "uv_arr:" << "(" << m.uv_count << ")" << endl;
	for(int i = 0; i < m.uv_count; ++i){
		cout << i << ": (" << m.uv_arr[2*i] << ", " << m.uv_arr[2*i+1] << ") " << endl;
	}
	cout << endl;
	cout << "normal_arr:" << "(" << m.normal_count << ")" <<endl;
	for(int i = 0; i < m.normal_count; ++i){
		cout << i << ": (" << m.normal_arr[3*i] << ", " << m.normal_arr[3*i+1] << ", " << m.normal_arr[3*i+2] << ") " << endl;
	}
	cout << endl;
	cout << "index_arr: " << "(" <<m.index_count << ")" << endl;
	for(int i = 0; i < m.index_count; ++i){
		cout << i << ": " << "v" << m.index_arr[i] << endl;
	}
}

int main(int argc, char* argv[]){
	char path[] = "cubo1.obj";
	modelo m = load_obj(path);
	print_modelo(m);
}