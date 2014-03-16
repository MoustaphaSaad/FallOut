#include"ObjectBehavior.h"
#include"Engine.h"
ObjectBehavior::ObjectBehavior(VObject* object){
	parent = object;
	input = Engine::getEngine()->getInputManager();
}

ObjectBehavior::~ObjectBehavior(){

}