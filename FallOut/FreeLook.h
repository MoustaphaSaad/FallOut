#ifndef FREELOOK_H
#define FREELOOK_H
#include"ObjectBehavior.h"
#include"GameObject.h"
#include"Engine.h"
namespace Fallout{
class FreeLook : public ObjectBehavior{
	bool mouseLocked;
public:
	FreeLook() :ObjectBehavior(){
		mouseLocked = false;
	}
	void Input(){
		float sensitivity = 0.5f;
		float movAmt = (float)(5);
		float rotAmt = (float)(Time::getDelta());

		if(input->getMouseButton(0)==keyState::UP){
			mouseLocked=false;
		}
		
		if(mouseLocked){
			float CX = Engine::getInstance()->getDisplay()->width / 2;
			float CY = Engine::getInstance()->getDisplay()->height / 2;
			vec2 centerPosition = vec2(CX,CY);
			vec2 deltaPos = input->getMousePosition() - centerPosition;

			bool rotY = deltaPos.GetX() !=0;
			bool rotX = deltaPos.GetY() !=0;
			
			if (rotY)
				parent->getTransform()->Rotate(vec3(0,1,0), ToRadians(deltaPos.GetX()*sensitivity));
			if(rotX)
				parent->getTransform()->Rotate(parent->getTransform()->rotation.GetRight(), ToRadians(deltaPos.GetY()*sensitivity));
			if(rotX||rotY)
				input->setMousePosition(centerPosition);
		}

		if(input->getMouseButton(0)==keyState::DOWN){
			float CX = Engine::getInstance()->getDisplay()->width / 2;
			float CY = Engine::getInstance()->getDisplay()->height / 2;
			vec2 centerPosition = vec2(CX,CY);
			input->setMousePosition(centerPosition);
			mouseLocked = true;
		}
	}
};
}
#endif