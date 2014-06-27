#ifndef FREEMOVE_H
#define FREEMOVE_H
#include"ObjectBehavior.h"
#include"GameObject.h"
#include"Engine.h"
namespace Fallout{
class FreeMove : public ObjectBehavior{
	bool mouseLocked;
public:
	FreeMove() :ObjectBehavior(){
		mouseLocked = false;
	}
	void Input(){
		float sensitivity = 0.5f;
		float movAmt = (float)(5);
		float rotAmt = (float)(Time::getDelta());
		
		vec3 f = parent->getTransform()->rotation.GetForward();
		if(input->getKey('w')==keyState::DOWN){
			parent->getTransform()->move(parent->getTransform()->rotation.GetForward(), movAmt);
		}
		if(input->getKey('s')==keyState::DOWN){
			parent->getTransform()->move(parent->getTransform()->rotation.GetBack(), movAmt);
		}
		if(input->getKey('a')==keyState::DOWN){
			parent->getTransform()->move(parent->getTransform()->rotation.GetLeft(), movAmt);
		}
		if(input->getKey('d')==keyState::DOWN){
			parent->getTransform()->move(parent->getTransform()->rotation.GetRight(), movAmt);
		}
		if (input->getKey('q') == keyState::DOWN)
			parent->getTransform()->Rotate(parent->getTransform()->rotation.GetForward(), rotAmt*sensitivity);
		if (input->getKey('e') == keyState::DOWN)
			parent->getTransform()->Rotate(parent->getTransform()->rotation.GetForward(), -rotAmt*sensitivity);
	}
};
}
#endif
