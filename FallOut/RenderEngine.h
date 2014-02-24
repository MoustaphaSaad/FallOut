#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include"GameObject.h"
#include"Mesh.h"
class Scene;
class Engine;
class RenderEngine{
public:
	RenderEngine();
	~RenderEngine();

	void drawMesh(Mesh* obj);
	void drawGameObject(GameObject* obj);
	void drawScene(Scene* obj);
private:
	Engine* engine;
};
#endif