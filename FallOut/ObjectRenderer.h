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

	void setParent(Transformable* prnt){
		parent = prnt;
	}
	Transformable* getParent(){
		return parent;
	}

protected:
	vector<Mesh*> Meshes;
};
#endif
