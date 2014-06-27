#include"Display.h"
#include"Engine.h"
using namespace Fallout;
void Display::BindTarget(){
	Engine::getInstance()->getGXManager()->bindBuffer(Buffer::Type::FRAMEBUFFER,0,Engine::getInstance()->getDisplay()->width,Engine::getInstance()->getDisplay()->height);
}