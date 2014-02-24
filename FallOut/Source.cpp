#include<iostream>
#include"FallOut.h"
using namespace std;
class Tu : public Application{
public:
	GameObject* obj;
	double e;
	Mesh* eo;
	Tu():Application(){
		e=0;
	}
	void init(){
		Shader* shoho = resourceManager->createShader("basic","res/basic.glsl");
		eo =resourceManager->createMesh("moka","res/moksa.obj");
		eo->getMaterial()->setShader(shoho);
		obj = new GameObject(new Transform());
		obj->setRenderComponent(new ObjectRenderer(eo));
		obj->getTransform()->position.SetZ(4);
		scene->addChild(obj);
	}
	void input(){
		if(Input->getKey('w') == keyState::DOWN)
			scene->getCamera()->move(vec3(0,0,0.01));
	}
	void postRender(){
		e=Time::getElapsedTime();
		Shader* shoho = eo->getMaterial()->getShader();
		eo->getMaterial()->use();
		shoho->setUniform("lightPosition",vec3(0,0,-2));
		shoho->setUniform("MVP",scene->getCamera()->getProjection()*scene->getCamera()->getPositionRotation()*obj->getTransform()->getMVP());
		shoho->setUniform("MV",obj->getTransform()->getMVP());
		obj->getTransform()->rotation.SetY((sin(e)*180));
	}
};
int main(){
	Engine* e = Engine::getEngine();
	e->initiate(new Display(800,600,"tr"),GraphicsHandle::OpenGL);
	Tu* app = new Tu();
	//e->setClearColor(vec3(0,0,0));
	e->start(app);
	return 0;
}