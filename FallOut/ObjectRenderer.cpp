#include"ObjectRenderer.h"
#include"Engine.h"
#include"Shader.h"
using namespace Fallout;
DefaultRenderer::DefaultRenderer(GameObject* parent, Mesh* m) :GameComponent(){
	Meshes.push_back(m);
}

DefaultRenderer::DefaultRenderer(GameObject* parent, vector<Mesh*> m) : GameComponent(){
	Meshes = vector<Mesh*>(m);
}

DefaultRenderer::DefaultRenderer() : GameComponent(){
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