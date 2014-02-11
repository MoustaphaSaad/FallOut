#include"Engine.h"
#include"FallOut.h"
Engine* Engine::engine = NULL;

Engine::Engine(){
		gxManager = NULL;
		resourceManager = NULL;
		display = NULL;
		engine = this;
}
Engine* Engine::getEngine(){
	return engine;
}
GXManager* Engine::getGXManager(){
	return gxManager;
}
Display* Engine::getDisplay(){
	return display;
}
void Engine::setClearColor(vec3 v){
	gxManager->setClearColor(v);
}
void Engine::initiate(Display d,GraphicsHandle h){
	initMembers(h,d);
	gxManager->setClearColor(vec3(0,0,0));
}
void Engine::start(){
	init();
	gxManager->start();
}
Engine::~Engine(){
	delete gxManager;
}

void Engine::init(){
	Shader* shoho = resourceManager->createShader("basic","res/basic.glsl");
	Mesh* oi =resourceManager->createMesh("cube","res/moksa.obj");
}
void Engine::initMembers(GraphicsHandle h,Display d){
	display = &d;
	if(h == GraphicsHandle::OpenGL){
		gxManager = new OpenGLManager(d);
	}else if(h == GraphicsHandle::DirectX){
		//TODO : DirectX Manager
		//gxManager = new DirectXManager(d);
	}else{
		gxManager = NULL;
	}
	resourceManager = ResourceManager::getInstance();
}