#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include"GameObject.h"
#include"Mesh.h"
class Engine;
class RenderEngine{
public:
	RenderEngine();
	~RenderEngine();

	void drawMesh(Mesh* obj);
	void drawGameObject(GameObject* obj);
private:
	Engine* engine;
};
#endif