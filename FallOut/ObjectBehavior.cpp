#include"ObjectBehavior.h"
#include"Engine.h"
using namespace Fallout;
ObjectBehavior::ObjectBehavior() :GameComponent(){
	input = Engine::getInstance()->getInputManager();
}

ObjectBehavior::~ObjectBehavior(){

}