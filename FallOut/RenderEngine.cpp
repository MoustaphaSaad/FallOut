#include"RenderEngine.h"
#include"Shader.h"
#include"Engine.h"
#include"Scene.h"
RenderEngine::RenderEngine(){
	engine = Engine::getInstance();
}
RenderEngine::~RenderEngine(){
	delete engine;
}

void RenderEngine::drawMesh(Mesh* obj){
	if(!obj)
		return;
	engine->getGXManager()->drawGeometry(obj->getGeometry(),obj->vbo,obj->ibo);
	for(int j=0;j<obj->getSubMeshCount();j++){
			obj->getSubMesh(j)->getMaterial()->use();
			Engine::getInstance()->getRenderer()->drawMesh(obj->getSubMesh(j));
	}
	engine->getGXManager()->BindShader(0);
	engine->getGXManager()->BindTexture(0,0);
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