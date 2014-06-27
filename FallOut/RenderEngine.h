#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include"GameObject.h"
#include"Mesh.h"
#include"FrameBuffer.h"
namespace Fallout{
class ShadowShader;
class Scene;
class Engine;

class RenderEngine{
	friend class Engine;
	friend class IPU;
public:
	enum RenderState{Normal,Shadow,Custom};
	RenderEngine();
	~RenderEngine();

	void Draw(Transformable* sender, Mesh* mesh,Shader* shdr=NULL);
	void render(Scene* scene);
	void renderToBuffer(FrameBuffer* buffer,Scene* scene = NULL,Shader* shdr = NULL);
private:
	void shadowPhase(Scene* scene);
	RenderState state;

	ShadowShader* shadowShader;
	Engine* engine;
};
}
#endif