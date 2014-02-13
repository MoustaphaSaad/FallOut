#ifndef ENGINE_H
#define ENGINE_H
#include"Resources.h"
#include"OpenGLManager.h"
#include"RenderEngine.h"
enum GraphicsHandle{ OpenGL,DirectX};

class Engine{
public:
	

	Engine();
	static Engine* getEngine();
	GXManager* getGXManager();
	RenderEngine* getRenderer();
	void initiate(Display d,GraphicsHandle h);
	void start();
	void setClearColor(vec3);
	Display* getDisplay();
	~Engine();
private:
	void init();
	void initMembers(GraphicsHandle h,Display d);

	GXManager* gxManager;
	static Engine* engine;
	Display* display;
	ResourceManager* resourceManager;
	RenderEngine* rEngine;
};
#endif