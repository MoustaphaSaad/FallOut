#ifndef OBJLOADER_H
#define OBJLOADER_H
#include"Mesh.h"
#include<fstream>
#include<vector>
#include<string>
using namespace std;
namespace Fallout{
class ObjLoader{
public:
	static Mesh* loadObj(string filename);
};
}
#endif