#ifndef CORE_H_
#define CORE_H_
class Engine;
class InputManager;
class RenderEngine;
class ResourceManager;
class GXManager;
namespace Fallout{
	Engine* getEngine();
	InputManager* getInputManager();
	RenderEngine* getRenderer();
	ResourceManager* getResourceManager();
	GXManager* getGXManager();
}
#endif