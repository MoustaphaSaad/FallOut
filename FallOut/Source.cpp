#include<iostream>
#include"FallOut.h"
using namespace std;
int main(){
	Engine* e = Engine::getEngine();
	e->initiate(Display(800,600,"tr"),GraphicsHandle::OpenGL);
	Application* app = new Application();
	//e.setClearColor(vec3(1,0,0));
	e->start(app);
	return 0;
}