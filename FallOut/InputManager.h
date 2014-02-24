#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include<vector>
#include"Math3D.h"
using namespace std;
enum keyState{
	DOWN,UP,NONE
};
class InputManager{
protected:
	static vector<pair<unsigned char,keyState> > Keys;
	static vector<pair<unsigned char,keyState> > Mouse;
	static vec2 mousePosition;
public:
	virtual void update();
	keyState getKey(unsigned int key);
	keyState getMouseButton(unsigned int key);
	virtual void setMousePosition(vec2 pos){}
	vec2 getMousePosition();
};
#endif