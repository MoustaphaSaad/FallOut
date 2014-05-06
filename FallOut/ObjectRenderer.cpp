#include"ObjectRenderer.h"
#include"Engine.h"
#include"Shader.h"

ObjectRenderer::ObjectRenderer(Mesh* m){
	Meshes.push_back(m);
	parent = NULL;
}

ObjectRenderer::ObjectRenderer(vector<Mesh*> m){
	Meshes = vector<Mesh*>(m);
}

ObjectRenderer::ObjectRenderer(){
	Meshes = vector<Mesh*>();
}
ObjectRenderer::~ObjectRenderer(){
	for(int i=0;i<Meshes.size();i++)
		delete Meshes[i];
	Meshes.clear();
}


void ObjectRenderer::Render(){
	for(int i=0;i<Meshes.size();i++){
		Meshes[i]->getMaterial()->use();
		Meshes[i]->getMaterial()->getShader()->Update(parent);
		Engine::getInstance()->getRenderer()->drawMesh(Meshes[i]);
	}
}

void ObjectRenderer::Render(Shader* shdr){
	for (int i = 0; i<Meshes.size(); i++){
		shdr->Bind();
		shdr->Update(parent);
		Engine::getInstance()->getRenderer()->drawMesh(Meshes[i]);
	}
}