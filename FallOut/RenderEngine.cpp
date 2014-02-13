#include"RenderEngine.h"
#include"Engine.h"
RenderEngine::RenderEngine(){
	engine = Engine::getEngine();
}
RenderEngine::~RenderEngine(){
	delete engine;
}

void RenderEngine::drawMesh(Mesh* obj){
	if(!obj->material){
		//callMaterial
	}
	engine->getGXManager()->drawGeometry(obj->getGeometry(),obj->vbo,obj->ibo);
}

void RenderEngine::drawGameObject(GameObject* obj){
	obj->RenderComponent->Render();
	for (auto it : obj->childList){
		it->Render();
	}
}