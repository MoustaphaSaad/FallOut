#ifndef MESH_H_
#define MESH_H_
#include"Resource.h"
#include"Geometry.h"
#include"Material.h"
#include<string>
using namespace std;
class Mesh:public Resource{
	friend class RenderEngine;
public:
	Mesh(const string name,Geometry* geo,Material* mat);
	//Mesh(const string name);
	Mesh(Geometry* geo,Material* mat);
	~Mesh();

	Geometry* getGeometry();
	Material* getMaterial();

	void setGeometry(Geometry val);
	void setMaterial(Material* val);

	void draw();
private:
	Geometry* geometry;
	Material* material;
	unsigned int vbo,ibo;
};
#endif