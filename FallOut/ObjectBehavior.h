#ifndef OBJECTBEHAVIOR_H_
#define OBJECTBEHAVIOR_H_
#include"Component.h"
#include"VisualObject.h"
#include"InputManager.h"
class ObjectBehavior:public Updatable{
protected:
	InputManager* input;
	Transformable* parent;
public:
	ObjectBehavior(Transformable* object = 0);
	~ObjectBehavior();


	void Input(){}
	void Update(){}

	void setParent(Transformable* prnt){
		parent = prnt;
	}
	Transformable* getParent(){
		return parent;
	}
};
#endif