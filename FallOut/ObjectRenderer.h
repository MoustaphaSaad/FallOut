#ifndef OBJECTRENDERER_H_
#define OBJECTRENDERER_H_
#include"Component.h"
#include"Mesh.h"
#include<vector>
using namespace std;
class ObjectRenderer : public Component{
public:
	ObjectRenderer(Mesh* m);
	ObjectRenderer(vector<Mesh*> m);
	ObjectRenderer();
	~ObjectRenderer();
	virtual void Input();
	virtual void Update();
	virtual void Render();

protected:
	vector<Mesh*> Meshes;
};
#endif
