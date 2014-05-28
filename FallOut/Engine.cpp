#include"Engine.h"
#include"FallOut.h"
#include<algorithm>
#include<iostream>
Engine* Engine::engine = NULL;

Engine::Engine(){
		gxManager = NULL;
		resourceManager = NULL;
		display = NULL;
		rEngine = NULL;
}
Engine* Engine::getInstance(){
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
	double delta;
	delta = min(passedTime, Time::frameLimit);
	if (Time::type == FPS::LIMITED)
		if (passedTime > Time::frameLimit)
			delta = passedTime;

	Time::frameTimeCount += delta;
	Time::timeCount += delta;

	bool draw = false;
	Time::lastTime = current;
	if (Time::frameTimeCount >= 1.0){
		std::cout << Time::frameCount << " || " << delta << std::endl;
		Time::frameCount = 0;
		Time::frameTimeCount = 0;
	}
	if (Time::type == FPS::LIMITED){
		if (Time::timeCount > Time::frameLimit){
			Time::update(Time::timeCount);
			input();
			draw = true;
			update(TimeStep(Time::timeCount,Time::g_Elapsed));
			Time::timeCount = 0;
		}
	}
	else if(Time::type == FPS::UNLIMITED){
		if (Time::timeCount > delta){
			Time::update(Time::timeCount);
			input();
			draw = true;
			update(TimeStep(Time::timeCount, Time::g_Elapsed));
			Time::timeCount = 0;
		}
	}
	if(draw){
		//ShadowPhase();
		render();
		gxManager->refresh();
		
		Time::frameCount++;
		Input->update();
	}
}
Engine::~Engine(){
	delete gxManager;
	delete engine;
}

void Engine::input(){
	if(app->scene!=NULL)
		app->scene->Input();
	app->input();
}

void Engine::update(TimeStep time){
	if(app->scene!=NULL)
		app->scene->Update(time);
	app->update();
}

void Engine::render(){
	gxManager->clearBuffers();
	gxManager->setClearColor(app->scene->getClearColor());
	app->postRender();
	rEngine->shadowPhase(app->scene);
	rEngine->render(app->scene);
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