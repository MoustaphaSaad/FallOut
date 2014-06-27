#include"Scene.h"
#include"Core.h"
#include"Timing.h"
using namespace Fallout;
Scene::Scene(){
	cam=new PerspectiveCamera(vec3(0,0,0),vec3(0,0,1),vec3(0,1,0),ToRadians(45.0f),1,100);
	clearColor = vec3(0,0,0);
	childList.push_back(cam);
}
Scene::~Scene(){
}

void Scene::Input(){
	GameObject::Input();
}
void Scene::Update(TimeStep time){
	GameObject::Update(time);
}
void Scene::Render(){
	GameObject::Render();
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

void Scene::addLight(light* val){
	ligths.push_back(val);
}
light* Scene::getLight(int val){
	return this->ligths[val];
}
int Scene::getLightsCount(){
	return ligths.size();
}

void Scene::addDirLight(DirectionalLight* val){
	DirLights.push_back(val);
}
DirectionalLight* Scene::getDirLight(int val){
	return DirLights[val];
}