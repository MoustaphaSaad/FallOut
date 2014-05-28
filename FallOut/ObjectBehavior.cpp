#include"ObjectBehavior.h"
#include"Engine.h"
ObjectBehavior::ObjectBehavior(Transformable* object) :GameComponent(ComponentType::BEHAVIOUR, object){
	input = Engine::getInstance()->getInputManager();
}

ObjectBehavior::~ObjectBehavior(){

}