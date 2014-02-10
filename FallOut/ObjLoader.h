#ifndef OBJLOADER_H
#define OBJLOADER_H
#include"Mesh.h"
#include<fstream>
#include<vector>
#include<string>
using namespace std;
class ObjLoader{
public:
	static Mesh* loadObj(const string resourceName,string filename);
};
#endif