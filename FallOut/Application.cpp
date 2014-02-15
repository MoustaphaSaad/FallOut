#include"Application.h"
Application::Application(){
	scene = new Scene();
	Engine = Engine::getEngine();
	resourceManager = ResourceManager::getInstance();
	gxManager = Engine->getGXManager();
}

void Application::init(){
}
void Application::input(){
}
void Application::update(){
}
void Application::setupScene(){
}
void Application::loadResources(){
}
void Application::postRender(){
}