#include"Application.h"
#include"Engine.h"
using namespace Fallout;
Application::Application(){
	scene = new Scene();
	Engine = Engine::getInstance();
	Input = Engine->getInputManager();
	rEngine = Engine->getRenderer();
	resourceManager = ResourceManager::getInstance();
	gxManager = Engine->getGXManager();
}
void Application::init(){
}
void Application::input(){
}
void Application::update(TimeStep gameTime){
}
void Application::setupScene(){
}
void Application::loadResources(){
}
void Application::postRender(){
}

Scene* Application::getScene(){
	return scene;
}

Application::~Application(){

}