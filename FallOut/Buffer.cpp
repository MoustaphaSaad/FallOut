#include"Buffer.h"
#include"Engine.h"
Buffer::Buffer(BufferType t, unsigned int x, unsigned int y) {
	type = t;
	width = x;
	height = y;
	ID = Engine::getInstance()->getGXManager()->createBuffer(type,x,y);
}
Buffer::Buffer(BufferType t) {
	type = t;
	width = Engine::getInstance()->getDisplay()->width;
	height = Engine::getInstance()->getDisplay()->height;
	ID = Engine::getInstance()->getGXManager()->createBuffer(type, width,height);
}

Buffer::~Buffer(){
	Engine::getInstance()->getGXManager()->deleteBuffer(type, ID);
}

void Buffer::bind(){
	Engine::getInstance()->getGXManager()->bindBuffer(type, ID);
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

BufferType Buffer::getType(){
	return type;
}
void Buffer::unbind(BufferType type){
	Engine::getInstance()->getGXManager()->bindBuffer(type, 0);
}