#include"ObjectRenderer.h"
#include"Engine.h"
#include"Shader.h"

DefaultRenderer::DefaultRenderer(Transformable* parent, Mesh* m) :GameComponent(ComponentType::RENDERER, parent){
	Meshes.push_back(m);
}

DefaultRenderer::DefaultRenderer(Transformable* parent, vector<Mesh*> m) : GameComponent(ComponentType::RENDERER, parent){
	Meshes = vector<Mesh*>(m);
}

DefaultRenderer::DefaultRenderer() : GameComponent(ComponentType::RENDERER){
	Meshes = vector<Mesh*>();
}
DefaultRenderer::~DefaultRenderer(){
	for(int i=0;i<Meshes.size();i++)
		delete Meshes[i];
	Meshes.clear();
}


void DefaultRenderer::Render(){
	for(int i=0;i<Meshes.size();i++){
		Engine::getInstance()->getRenderer()->Draw(parent,Meshes[i]);
	}
}