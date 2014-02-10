#include<iostream>
#include"FallOut.h"
using namespace std;
int main(){
	Engine e;
	e.initiate(Display(800,600,"tr"),GraphicsHandle::OpenGL);
	//e.setClearColor(vec3(1,0,0));
	e.start();
	return 0;
}