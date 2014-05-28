#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H
#include"Transform.h"
class Transformable;
class Transformable{
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