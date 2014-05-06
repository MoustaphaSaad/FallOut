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
	void drawGameObject(GameObject* obj,Shader* shdr);
	void drawScene(Scene* obj);
	void drawScene(Scene* obj,Shader* shdr);
private:
	
	Engine* engine;
};
#endif