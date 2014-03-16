#include"Engine.h"
#include"FallOut.h"
Engine* Engine::engine = NULL;

Engine::Engine(){
		gxManager = NULL;
		resourceManager = NULL;
		display = NULL;
		rEngine = NULL;
}
Engine* Engine::getEngine(){
	if(!engine){
		engine = new Engine();
	}
	return engine;
}
GXManager* Engine::getGXManager(){
	return gxManager;
}
Display* Engine::getDisplay(){
	return display;
}
InputManager* Engine::getInputManager(){
	return Input;
}
RenderEngine* Engine::getRenderer(){
	return rEngine;
}
void Engine::setClearColor(vec3 v){
	gxManager->setClearColor(v);
}
void Engine::initiate(Display* d,GraphicsHandle h){
	initMembers(h,d);
}
void Engine::start(Application* app){
	this->app = app;
	init();
	Time::init();
	gameLoop();
	gxManager->start();
}
void Engine::gameLoop(){
	double current = Time::getTime();
	double passedTime = current - Time::lastTime;
	Time::frameTimeCount +=passedTime;
	Time::timeCount += passedTime;
	bool draw = false;
	Time::lastTime = current;

	if(Time::frameTimeCount>=1.0){
		Time::frameCount = 0;
		Time::frameTimeCount = 0;
	}
	if(Time::timeCount>=Time::frameLimit){
		Time::update(Time::frameLimit);
		input();
		draw = true;
		update();
		Time::timeCount -=Time::frameLimit;
	}
	if(draw){
		render();
		gxManager->refresh();
		Time::frameCount++;
		Input->update();
	}
}
Engine::~Engine(){
	delete gxManager;
}

void Engine::input(){
	if(app->scene!=NULL)
		app->scene->Input();
	app->input();
}

void Engine::update(){
	if(app->scene!=NULL)
		app->scene->Update();
	app->update();
}

void Engine::render(){
	gxManager->setClearColor(app->scene->getClearColor());
	app->postRender();
	if(app->scene!=NULL){
		app->scene->Render();
		rEngine->drawScene(app->scene);
	}
}

void Engine::init(){
	app->init();
	app->loadResources();
	app->setupScene();
}
void Engine::initMembers(GraphicsHandle h,Display* d){
	display = d;
	if(h == GraphicsHandle::OpenGL){
		gxManager = new OpenGLManager(d);
		Input = new InputGL();
	}else if(h == GraphicsHandle::DirectX){
		//TODO : DirectX Manager
		//gxManager = new DirectXManager(d);
		//Input = new InputDX();
	}else{
		gxManager = NULL;
	}
	resourceManager = ResourceManager::getInstance();
	rEngine = new RenderEngine();
}

Application* Engine::getApplication(){
	return app;
}