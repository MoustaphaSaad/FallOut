#ifndef OBJECTBEHAVIOR_H_
#define OBJECTBEHAVIOR_H_
#include"Component.h"
#include"VisualObject.h"
#include"InputManager.h"
class ObjectBehavior:public Updatable{
protected:
	InputManager* input;
	VObject* parent;
public:
	ObjectBehavior(VObject* object=0);
	~ObjectBehavior();


	void Input(){}
	void Update(){}

	void setParent(VObject* prnt){
		parent = prnt;
	}
	VObject* getParent(){
		return parent;
	}
};
#endif