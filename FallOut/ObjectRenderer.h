#ifndef OBJECTRENDERER_H_
#define OBJECTRENDERER_H_
#include"Component.h"
#include"Mesh.h"
class ObjectRenderer : public Component{
public:
	ObjectRenderer(Mesh* m);
	ObjectRenderer();
	~ObjectRenderer();
	virtual void Input();
	virtual void Update();
	virtual void Render();

protected:
	Mesh* mesh;
};
#endif
