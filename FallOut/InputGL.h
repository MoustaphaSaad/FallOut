#ifndef INPUTGL_H
#define INPUTGL_H
#include"InputManager.h"
namespace Fallout{
class InputGL:public InputManager{
public:
	static void keyboardDownFunc(unsigned char k,int x,int y);
	static void keyboardUpFunc(unsigned char k,int x,int y);
	static void mouseFunc(int button,int state,int x,int y);
	static void mouseMotionFunc(int x,int y);

	void update();
	void setMousePosition(vec2 val);


};

}


#endif