#include"GameObject.h"

#include"Engine.h"
#include<algorithm>

GameObject::GameObject(Transform* transform):Transformable(transform){
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
	Engine::getEngine()->getRenderer()->drawGameObject(this);
}

void GameObject::addChild(GameObject* child){
	childList.push_back(child);
	child->setParent(this);
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

void GameObject::setRenderComponent(ObjectRenderer* val){
	val->setParent(this);
	RenderComponent = val;
}
void GameObject::setBehaviorComponent( ObjectBehavior* val){
	val->setParent(this);
	BehaviorComponent = val;
}
Renderable GameObject::getRenderComponent(){
	return *RenderComponent;
}
Updatable GameObject::getBehaviorComponent(){
	return *BehaviorComponent;
}
GameObject::~GameObject(){
	childList.clear();
	delete RenderComponent;
	delete BehaviorComponent;
}