#include"Core.h"
#include"Engine.h"
using namespace Fallout;
Engine* Fallout::getEngine(){
	return Engine::getInstance();
}
InputManager* Fallout::getInputManager(){
	return getEngine()->getInputManager();
}
RenderEngine* Fallout::getRenderer(){
	return getEngine()->getRenderer();
}
ResourceManager* Fallout::getResourceManager(){
	return ResourceManager::getInstance();
}
GXManager* Fallout::getGXManager(){
	return getEngine()->getGXManager();
}
Application* Fallout::getApplication(){
	return getEngine()->getApplication();
}
Display* Fallout::getDisplay(){
	return getEngine()->getDisplay();
}