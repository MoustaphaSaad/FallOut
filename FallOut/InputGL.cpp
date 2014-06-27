#include"InputGL.h"
#include<GL\freeglut.h>
using namespace Fallout;
void InputGL::keyboardDownFunc(unsigned char k,int x,int y){
	Keys.push_back(make_pair(k,keyState::DOWN));
}
void InputGL::keyboardUpFunc(unsigned char k,int x,int y){
	Keys.push_back(make_pair(k,keyState::UP));
}

void InputGL::mouseFunc(int button,int state,int x,int y){
	mousePosition.SetX(x);
	mousePosition.SetY(y);
	if(state == GLUT_DOWN)
		Mouse.push_back(make_pair(button,keyState::DOWN));
	else if (state = GLUT_UP)
		Mouse.push_back(make_pair(button,keyState::UP));
}

void InputGL::mouseMotionFunc(int x,int y){
	mousePosition.SetX(x);
	mousePosition.SetY(y);
}

void InputGL::setMousePosition(vec2 pos){
	mousePosition = pos;
	glutWarpPointer(pos.GetX(),pos.GetY());
}

void InputGL::update(){
	Keys.clear();
	Mouse.clear();
}