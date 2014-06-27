#ifndef COMPONENT_H
#define COMPONENT_H
#include<iostream>
#include<memory>
#include"Timing.h"
#include"VisualObject.h"
using namespace std;
namespace Fallout{
	class GameComponent;
	typedef tr1::shared_ptr<GameComponent> GameComponentPtr;
class GameObject;
class GameComponent{
	friend class GameObject;
protected:
	Transformable* parent;
public:

	GameComponent(){
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

}
#endif