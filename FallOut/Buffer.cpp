#include"Buffer.h"
#include"Engine.h"
using namespace Fallout;
Buffer::Buffer(Type t, unsigned int x, unsigned int y) {
	type = t;
	width = x;
	height = y;
	ID = Engine::getInstance()->getGXManager()->createBuffer(type,x,y);
}
Buffer::Buffer(Type t) {
	type = t;
	width = Engine::getInstance()->getDisplay()->width;
	height = Engine::getInstance()->getDisplay()->height;
	ID = Engine::getInstance()->getGXManager()->createBuffer(type, width,height);
}

Buffer::~Buffer(){
	Engine::getInstance()->getGXManager()->deleteBuffer(type, ID);
}

void Buffer::bind(){
	Engine::getInstance()->getGXManager()->bindBuffer(type, ID,width,height);
}

unsigned int Buffer::getID(){
	return ID;
}

unsigned int Buffer::getHeight(){
	return height;
}

unsigned int Buffer::getWidth(){
	return width;
}

Buffer::Type Buffer::getType(){
	return type;
}
void Buffer::unbind(Type type){
	Engine::getInstance()->getGXManager()->bindBuffer(type, 0,Engine::getInstance()->getDisplay()->width,Engine::getInstance()->getDisplay()->height);
}