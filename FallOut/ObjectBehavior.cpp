#include"ObjectBehavior.h"
#include"Engine.h"
ObjectBehavior::ObjectBehavior(Transformable* object){
	parent = object;
	input = Engine::getInstance()->getInputManager();
}

ObjectBehavior::~ObjectBehavior(){

}