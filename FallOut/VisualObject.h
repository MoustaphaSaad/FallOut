#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H
#include"Transform.h"
class Transformable;
class VObject{
protected:
	VObject* parent;
public:
	VObject(){
	}
	~VObject(){
	}
	VObject* getParent(){
		return parent;
	}
	void setParent(VObject* prnt){
		parent = prnt;
	}
};
class Transformable:public VObject{
protected:
	Transform* transform;
public:
	Transformable(Transform* trans = new Transform()){
		transform = trans;
	}
	~Transformable(){
		delete transform;
	}

	void setTransform(Transform* trans){
		transform = trans;
	}
	Transform* getTransform(){
		return transform;
	}
};
#endif