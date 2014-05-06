#include"Engine.h"
#include"FallOut.h"
#include<algorithm>
#include<iostream>
#include"SimpleShader.h"
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
void initFBO(){
	int w = 800;
	int h = 600;

	glGenFramebuffers(1, &Fallout::getEngine()->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, Fallout::getEngine()->FBO);

	glGenRenderbuffers(1, &Fallout::getEngine()->renderT);
	glBindRenderbuffer(GL_RENDERBUFFER, Fallout::getEngine()->renderT);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, Fallout::getEngine()->renderT);

	glGenRenderbuffers(1, &Fallout::getEngine()->depth);
	glBindRenderbuffer(GL_DEPTH_BUFFER, Fallout::getEngine()->depth);
	glRenderbufferStorage(GL_DEPTH_BUFFER, GL_DEPTH_COMPONENT, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_DEPTH_BUFFER, Fallout::getEngine()->depth);


	glGenTextures(1,& Fallout::getEngine()->dtex);
	glBindTexture(GL_TEXTURE_2D, Fallout::getEngine()->dtex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Fallout::getEngine()->dtex, 0);

	glGenTextures(1, &Fallout::getEngine()->rtexs);
	glBindTexture(GL_TEXTURE_2D, Fallout::getEngine()->rtexs);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Fallout::getEngine()->rtexs, 0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindRenderbuffer(GL_DEPTH_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}
void Engine::start(Application* app){
	this->app = app;
	init();
	Time::init();
	initFBO();
	gameLoop();
	gxManager->start();
}

void Engine::ShadowPhase(){
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, txt->getID(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glBindRenderbuffer(GL_RENDERBUFFER, Fallout::getEngine()->renderT);
	glBindRenderbuffer(GL_DEPTH_BUFFER, Fallout::getEngine()->depth);

	vec3 tPos = app->scene->getCamera()->getTransform()->position;
	vec4 tRot = app->scene->getCamera()->getTransform()->rotation;
	
	app->scene->getCamera()->getTransform()->position = app->scene->dirLight->getPosition();
	app->scene->getCamera()->getTransform()->rotation = app->scene->getCamera()->getTransform()->getLookAtRot(app->scene->dirLight->getDirection(),app->scene->dirLight->getTransform()->rotation.GetUp());

	float arr[4][4] = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0.5f, 0.5f, 0.5f, 1.0f
	};

	mat4 scaleBias(arr);
	PerspectiveCamera* Acam = (PerspectiveCamera*)app->scene->getCamera();

	shadowMatrix = scaleBias*app->scene->getCamera()->getProjection()*app->scene->getCamera()->getPositionRotation();
	glCullFace(GL_FRONT);
	render();
	glCullFace(GL_BACK);

	app->scene->getCamera()->getTransform()->position = tPos;
	app->scene->getCamera()->getTransform()->rotation = tRot;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindRenderbuffer(GL_DEPTH_BUFFER, 0);
}
void Engine::gameLoop(){

	double current = Time::getTime();
	double passedTime = current - Time::lastTime;
	Time::frameTimeCount +=passedTime;
	Time::timeCount += passedTime;
	double delta = min(passedTime, (double)Time::frameLimit);
	bool draw = false;
	Time::lastTime = current;

	if(Time::frameTimeCount>=1.0){
		std::cout << Time::frameCount<<" || "<< Time::frameTimeCount << std::endl;
		Time::frameCount = 0;
		Time::frameTimeCount = 0;
	}
	while(Time::timeCount>=delta){
		Time::update(delta);
		input();
		draw = true;
		update();
		Time::timeCount -= delta;
	}
	if(true){
		ShadowPhase();
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
	OpenGLManager* ogl = (OpenGLManager*)gxManager;
	ogl->clearBuffers();
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