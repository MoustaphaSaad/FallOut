#ifndef OBJECTRENDERER_H_
#define OBJECTRENDERER_H_
#include"Component.h"
#include"VisualObject.h"
#include"Mesh.h"
#include<vector>
using namespace std;

class ObjectRenderer : public Renderable{
	Transformable* parent;
public:
	ObjectRenderer(Mesh* m);
	ObjectRenderer(vector<Mesh*> m);
	ObjectRenderer();
	~ObjectRenderer();

	virtual void Render();
	virtual void Render(Shader* shdr);

	void setParent(Transformable* prnt){
		parent = prnt;
	}
	Transformable* getParent(){
		return parent;
	}
	Mesh* getMesh(int ix){
		if (ix < Meshes.size())
			return Meshes[ix];
	}

protected:
	vector<Mesh*> Meshes;
};
#endif
