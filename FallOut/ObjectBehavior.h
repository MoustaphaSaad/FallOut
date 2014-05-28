#ifndef OBJECTBEHAVIOR_H_
#define OBJECTBEHAVIOR_H_
#include"Component.h"
#include"VisualObject.h"
#include"InputManager.h"
class ObjectBehavior:public GameComponent{
	friend class GameObject;
protected:
	InputManager* input;
public:
	ObjectBehavior(Transformable* object);
	~ObjectBehavior();


	virtual void Input(){}
	virtual void Update(){}
	virtual void Render(){}
};
#endif