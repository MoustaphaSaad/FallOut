#ifndef COMPONENT_H
#define COMPONENT_H
#include<iostream>
#include<memory>
#include"Timing.h"
#include"VisualObject.h"
class GameObject;
enum ComponentType{RENDERER,BEHAVIOUR,XNONE};
class GameComponent{
protected:
	ComponentType type;
	Transformable* parent;
public:
	GameComponent(ComponentType type, Transformable* parent = 0){
		this->type = type;
		this->parent = parent;
	}
	ComponentType getType(){
		return type;
	}
	virtual void Input(){}
	virtual void Update(TimeStep time){}
	virtual void Render(){}

	Transformable* getParent(){
		return parent;
	}
	void setParent(Transformable* val){
		parent = val;
	}
};
#endif