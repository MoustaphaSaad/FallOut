#include"RenderEngine.h"
#include"Shader.h"
#include"Engine.h"
#include"Scene.h"
RenderEngine::RenderEngine(){
	engine = Engine::getEngine();
}
RenderEngine::~RenderEngine(){
	delete engine;
}

void RenderEngine::drawMesh(Mesh* obj){
	if(!obj)
		return;
	if(obj->material){
		obj->getMaterial()->getShader()->Bind();
	}
	engine->getGXManager()->drawGeometry(obj->getGeometry(),obj->vbo,obj->ibo);
}

void RenderEngine::drawGameObject(GameObject* obj){
	if(!obj)
		return;
	for (auto it : obj->childList){
		it->Render();
	}
	if(obj->RenderComponent!=NULL)
		obj->RenderComponent->Render();
}
void RenderEngine::drawScene(Scene* obj){
	if(!obj)
		return;
	engine->setClearColor(obj->clearColor);
	for (auto it : obj->childList){
		it->Render();
	}
}