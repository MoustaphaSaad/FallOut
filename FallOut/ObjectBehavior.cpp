#include"ObjectBehavior.h"
#include"Engine.h"
ObjectBehavior::ObjectBehavior(VObject* object){
	obj = object;
	input = Engine::getEngine()->getInputManager();
}

ObjectBehavior::~ObjectBehavior(){
	delete obj;
}

void ObjectBehavior::setObject(VObject* val){
	obj = val;
}
VObject* ObjectBehavior::getObject(){
	return obj;
}