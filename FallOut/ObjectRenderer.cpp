#include"ObjectRenderer.h"
#include"Engine.h"

ObjectRenderer::ObjectRenderer(Mesh* m){
	mesh = m;
}
ObjectRenderer::ObjectRenderer(){
	mesh = NULL;
}
ObjectRenderer::~ObjectRenderer(){
	delete mesh;
}

void ObjectRenderer::Input(){
}

void ObjectRenderer::Update(){
}

void ObjectRenderer::Render(){
	Engine::getEngine()->getRenderer()->drawMesh(mesh);
}
