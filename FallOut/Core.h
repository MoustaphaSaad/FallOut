#ifndef CORE_H_
#define CORE_H_
namespace Fallout{
	class Engine;
	class InputManager;
	class RenderEngine;
	class ResourceManager;
	class GXManager;
	class Display;
	class Application;
	Engine* getEngine();
	InputManager* getInputManager();
	RenderEngine* getRenderer();
	ResourceManager* getResourceManager();
	GXManager* getGXManager();
	Application* getApplication();
	Display* getDisplay();
}
#endif