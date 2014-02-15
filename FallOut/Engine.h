#ifndef ENGINE_H
#define ENGINE_H
#include"Resources.h"
#include"OpenGLManager.h"
#include"RenderEngine.h"
class Application;
enum GraphicsHandle{ OpenGL,DirectX};

class Engine{
	friend class OpenGLManager;
public:
	


	static Engine* getEngine();
	GXManager* getGXManager();
	RenderEngine* getRenderer();
	void initiate(Display d,GraphicsHandle h);
	void start(Application* app);
	void setClearColor(vec3);
	Display* getDisplay();
	~Engine();
private:
	Engine();
	void init();
	void initMembers(GraphicsHandle h,Display d);
	void input();
	void update();
	void render();

	Application* app;
	GXManager* gxManager;
	static Engine* engine;
	Display* display;
	ResourceManager* resourceManager;
	RenderEngine* rEngine;
};
#endif