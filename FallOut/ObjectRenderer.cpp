#include"ObjectRenderer.h"
#include"Engine.h"

ObjectRenderer::ObjectRenderer(Mesh* m){
	Meshes.push_back(m);
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

void ObjectRenderer::Input(){
}

void ObjectRenderer::Update(){
}

void ObjectRenderer::Render(){
	for(int i=0;i<Meshes.size();i++)
		Engine::getEngine()->getRenderer()->drawMesh(Meshes[i]);
}
