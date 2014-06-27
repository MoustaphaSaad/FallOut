#ifndef ENGINE_H
#define ENGINE_H
#include"Resources.h"
#include"OpenGLManager.h"
#include"RenderEngine.h"
#include"FrameBuffer.h"
#include"Application.h"
namespace Fallout{
class DepthTexture;
class InputManager;
class Engine{
	friend class OpenGLManager;
	friend class RenderEngine;
public:
	enum GraphicsHandle{ OpenGL,DirectX};
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
private:
	Engine();
	void init();
	void initMembers(GraphicsHandle h,Display* d);
	void input();
	void update(TimeStep time);
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
}
#endif