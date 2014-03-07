#ifndef OBJECTBEHAVIOR_H_
#define OBJECTBEHAVIOR_H_
#include"Component.h"
#include"VisualObject.h"
#include"InputManager.h"
class ObjectBehavior:public Component{
protected:
	VObject* obj;
	InputManager* input;
public:
	ObjectBehavior(VObject* object=0);
	~ObjectBehavior();

	VObject* getObject();
	void setObject(VObject* val);

	void Input(){}
	void Update(){}
	void Render(){}
};
#endif