#include"GameObject.h"
#include"ObjectRenderer.h"
#include"ObjectBehavior.h"
#include<algorithm>

GameObject::GameObject(const Transform transform){
	this->transform = transform;
	childList = vector<GameObject*>();
	RenderComponent = new ObjectRenderer();
	BehaviorComponent = new ObjectBehavior();
}

void GameObject::Input(){
	BehaviorComponent->Input();
	for (auto it : childList){
		it->Input();
	}
}
void GameObject::Update(){
	BehaviorComponent->Update();
	for (auto it : childList){
		it->Update();
	}
}
void GameObject::Render(){
	RenderComponent->Render();
	for (auto it : childList){
		it->Render();
	}
}

void GameObject::addChild(GameObject* child){
	childList.push_back(child);
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

Transform GameObject::getTransform(){
	return transform;
}

void GameObject::setTransform(const Transform transform){
	this->transform = transform;
}

void GameObject::setRenderComponent(Component* val){
	RenderComponent = val;
}
void GameObject::setBehaviorComponent( Component* val){
	BehaviorComponent = val;
}
Component GameObject::getRenderComponent(){
	return *RenderComponent;
}
Component GameObject::getBehaviorComponent(){
	return *BehaviorComponent;
}
GameObject::~GameObject(){
	childList.clear();
	delete RenderComponent;
	delete BehaviorComponent;
}