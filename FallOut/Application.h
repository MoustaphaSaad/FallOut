#ifndef APPLICATION_H
#define APPLICATION_H
#include"GXManager.h"
#include"Scene.h"
#include<memory>
using namespace std;
namespace Fallout{
	class Application;
	typedef tr1::shared_ptr<Application> ApplicationPtr;
class Application{

	friend class Engine;
public:
	Application();
	~Application();

	virtual void init();
	virtual void input();
	virtual void update(TimeStep gameTime);
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

}
#endif