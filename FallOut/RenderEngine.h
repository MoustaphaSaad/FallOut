#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include"GameObject.h"
#include"Mesh.h"
#include"FrameBuffer.h"
class SimpleShader;
class Scene;
class Engine;
enum RenderState{Normal,Shadow};
class RenderEngine{
	friend class Engine;
public:
	RenderEngine();
	~RenderEngine();

	void Draw(Transformable* sender, Mesh* mesh);
	void render(Scene* scene);
	void shadowPhase(Scene* scene);
	Texture* getDepth();
	mat4 getShadowMatrix(){
		return shadowMatrix;
	}
private:
	FrameBuffer *FB;
	mat4 shadowMatrix;
	RenderState state;
	SimpleShader* shadowShader;
	Engine* engine;
};
#endif