#include"GameObject.h"

#include"Engine.h"
#include"Timing.h"
#include<algorithm>
using namespace Fallout;
GameObject::GameObject(Transform* transform) :Transformable(transform), GameComponent(){
	childList = vector<GameObject*>();
	GCmap = map<string, GameComponent*>();
}

void GameObject::Input(){
	for (auto object : GCmap)
		object.second->Input();
	for (auto child : childList)
		child->Input();
}
void GameObject::Update(TimeStep time){
	for (auto object : GCmap)
		object.second->Update(time);
	for (auto child : childList)
		child->Update(time);
}
void GameObject::Render(){
	for (auto object : GCmap)
		object.second->Render();
	for (auto child : childList)
		child->Render();
}

void GameObject::addChild(GameObject* child){
	childList.push_back(child);
	child->setParent(this);
	child->getTransform()->setParentTransform(transform);
}
void GameObject::removeChild(GameObject* child){
	childList.erase(remove(childList.begin(),childList.end(),child),childList.end());
}
void GameObject::removeChild(int ix){
	childList.erase(childList.begin() + ix);
}
int GameObject::childrenCount(){
	return childList.size();
}

GameObject* GameObject::getChild(int ix){
	return childList[ix];
}

void GameObject::addComponent(string name,GameComponent* component){
	component->parent = this;
	GCmap.insert(make_pair(name, component));
}
GameComponent* GameObject::getComponent(string name){
	if (GCmap.find(name) != GCmap.end())
		return GCmap[name];
	return NULL;
}
GameObject::~GameObject(){
	childList.clear();
	GCmap.clear();
}