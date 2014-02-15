#include"Scene.h"
Scene::Scene(){
}
Scene::~Scene(){
}
Camera* Scene::getCamera(){
	return cam;
}
void Scene::setCamera(Camera* cam){
	this->cam = cam;
}