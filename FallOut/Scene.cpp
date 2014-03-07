#include"Scene.h"
Scene::Scene(){
	cam=new PerspectiveCamera();
	clearColor = vec3(0,0,0);
}
Scene::~Scene(){
}

void Scene::Input(){
	if(cam->camComp)
		cam->camComp->Input();
}
void Scene::Update(){
	if(cam->camComp)
		cam->camComp->Update();
}
void Scene::Render(){
	if(cam->camComp)
		cam->camComp->Render();
}
Camera* Scene::getCamera(){
	return cam;
}
void Scene::setCamera(Camera* cam){
	this->cam = cam;
}

void Scene::setClearColor(vec3 val){
	clearColor = val;
}
vec3 Scene::getClearColor(){
	return clearColor;
}
