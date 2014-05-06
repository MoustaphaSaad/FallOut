#ifndef ENGINE_H
#define ENGINE_H
#include"Resources.h"
#include"OpenGLManager.h"
#include"RenderEngine.h"
class Application;
enum GraphicsHandle{ OpenGL,DirectX};
class InputManager;
class Engine{
	friend class OpenGLManager;
	friend class RenderEngine;
public:
	static Engine* getInstance();
	GXManager* getGXManager();
	Application* getApplication();
	RenderEngine* getRenderer();
	void initiate(Display* d,GraphicsHandle h);
	void start(Application* app);
	void setClearColor(vec3);
	Display* getDisplay();
	InputManager* getInputManager();
	~Engine();
	GLuint FBO, renderT, depth,dtex,rtexs;
	mat4 shadowMatrix;
private:
	Engine();
	void init();
	void initMembers(GraphicsHandle h,Display* d);
	void input();
	void update();
	void render();
	void gameLoop();
	void ShadowPhase();

	Application* app;
	GXManager* gxManager;
	InputManager* Input;
	static Engine* engine;
	Display* display;
	ResourceManager* resourceManager;
	RenderEngine* rEngine;
};
#endif