#ifndef MESH_H_
#define MESH_H_
#include"Resource.h"
#include"Geometry.h"
#include"Material.h"
#include<string>
#include<vector>
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

	void updateGeometry(Geometry* val);

	void addSubMesh(Mesh* val);
	Mesh* getSubMesh(int i);
	int getSubMeshCount();

private:
	Geometry* geometry;
	Material* material;
	vector<Mesh*> subMesh;
	unsigned int vbo,ibo;
};
#endif