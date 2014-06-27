#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H
#include"Transform.h"
#include"VisualComposer.h"
namespace Fallout{
class Transformable{
protected:
	Transform* transform;
public:
	visualComposer* Composer;
	Transformable(Transform* trans = new Transform()){
		transform = trans;
		Composer = new visualComposer();
	}
	~Transformable(){
		delete transform;
		delete Composer;
	}

	void setTransform(Transform* trans){
		transform = trans;
	}
	Transform* getTransform(){
		return transform;
	}
};
}
#endif