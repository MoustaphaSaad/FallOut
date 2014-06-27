#ifndef MESH_H_
#define MESH_H_
#include"Resource.h"
#include"Geometry.h"
#include"Material.h"
#include<string>
#include<vector>
#include<memory>
using namespace std;
namespace Fallout{
	typedef tr1::shared_ptr<Mesh> MeshPtr;
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
	void setShader(Shader* shdr){
		material->setShader(shdr);
		for(int i=0;i<subMesh.size();i++)
			subMesh[i]->setShader(shdr);
	}

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

}
#endif