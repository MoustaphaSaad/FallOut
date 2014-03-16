#ifndef APPLICATION_H
#define APPLICATION_H
#include"Engine.h"
#include"Scene.h"
class Application{
	friend class Engine;
public:
	Application();
	~Application();

	virtual void init();
	virtual void input();
	virtual void update();
	virtual void setupScene();
	virtual void loadResources();
	virtual void postRender();

	Scene* getScene();
protected:
	Scene* scene;
	ResourceManager* resourceManager;
	Engine* Engine;
	InputManager* Input;
	RenderEngine* rEngine;
	GXManager* gxManager;
};
#endif