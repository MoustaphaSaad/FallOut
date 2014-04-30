#include<iostream>
#include"FallOut.h"
#include"Cloth.h"
#include"Atmosphere.h"
using namespace std;
class CamBe : public ObjectBehavior{
	bool mouseLocked;
public:
	CamBe(){
		mouseLocked = false;
	}
	void Input(){
		Camera* cam = (Camera*)parent;
		float sensitivity = 0.5f;
		float movAmt = (float)(Time::getDelta()*50);
		float rotAmt = (float)(Time::getDelta());

		if(input->getKey(Keys::KEY_ESCAPE)==keyState::DOWN){
			mouseLocked=false;
		}
		
		if(mouseLocked){
			float CX = Fallout::getEngine()->getDisplay()->width / 2;
			float CY = Fallout::getEngine()->getDisplay()->height / 2;
			vec2 centerPosition = vec2(CX,CY);
			vec2 deltaPos = input->getMousePosition() - centerPosition;

			bool rotY = deltaPos.GetX() !=0;
			bool rotX = deltaPos.GetY() !=0;
			
			if (rotY)
				cam->getTransform()->Rotate(vec3(0,1,0), ToRadians(deltaPos.GetX()*sensitivity));
			if(rotX)
				cam->getTransform()->Rotate(cam->getTransform()->rotation.GetRight(), ToRadians(deltaPos.GetY()*sensitivity));
			if(rotX||rotY)
				input->setMousePosition(centerPosition);
		}

		if(input->getMouseButton(0)==keyState::DOWN){
			float CX = Fallout::getEngine()->getDisplay()->width / 2;
			float CY = Fallout::getEngine()->getDisplay()->height / 2;
			vec2 centerPosition = vec2(CX,CY);
			input->setMousePosition(centerPosition);
			mouseLocked = true;
		}
		vec3 f = cam->getTransform()->rotation.GetForward();
		if(input->getKey('w')==keyState::DOWN){
			cam->move(cam->getTransform()->rotation.GetForward(), movAmt);
		}
		if(input->getKey('s')==keyState::DOWN){
			cam->move(cam->getTransform()->rotation.GetBack(), movAmt);
		}
		if(input->getKey('a')==keyState::DOWN){
			cam->move(cam->getTransform()->rotation.GetLeft(), movAmt);
		}
		if(input->getKey('d')==keyState::DOWN){
			cam->move(cam->getTransform()->rotation.GetRight(), movAmt);
		}
		if (input->getKey(Keys::KEY_q) == keyState::DOWN)
			cam->getTransform()->Rotate(cam->getTransform()->rotation.GetForward(), rotAmt*sensitivity);
		if (input->getKey(Keys::KEY_e) == keyState::DOWN)
			cam->getTransform()->Rotate(cam->getTransform()->rotation.GetForward(), -rotAmt*sensitivity);
	}
};
class Tu : public Application{
public:
	GameObject* obj;
	double e;
	Mesh* eo;
	Tu():Application(){
		e=0;
	}
	void init(){
		scene->getCamera()->setCamComp(new CamBe());
		Shader* shoho = new BasicShader();
		
		eo =resourceManager->createMesh("moka","res/moksa.obj");
		eo->getMaterial()->setShader(shoho);
		for(int i=0;i<eo->getSubMeshCount();i++){
			eo->getSubMesh(i)->getMaterial()->setShader(shoho);
		}
		obj = new GameObject(new Transform());
		obj->setRenderComponent(new ObjectRenderer(eo));
		obj->getTransform()->position.SetZ(10);
		//obj->getTransform()->scale.SetX(.1);
		//scene->addChild(obj);

		Cloth* cl = new Cloth(3, 3, 5, 5);
		cl->getTransform()->position.SetY(3);
		cl->getTransform()->position.SetZ(10);
		cl->getTransform()->position.SetX(-2);
		//scene->addChild(cl);
		Atmosphere* at = new Atmosphere();
		scene->addChild(at);

		//scene->getCamera()->getTransform()->Rotate(vec3(1, 0, 0), .5);
		//scene->getCamera()->getTransform()->position.SetX(5);
		//scene->getCamera()->getTransform()->position.SetZ(-10);
	}
	void setupScene(){
		light* l = new light();
		scene->addLight(l);
		l = new light();
		l->setPosition(vec3(-3,3,5));
		l->setLa(vec3(2,0,2));
		
		scene->addLight(l);
	}
	void input(){
		if(this->Input->getKey(27)==keyState::DOWN)
			cout<<"weijf"<<endl;
	}
	void postRender(){
		e+=Time::getDelta();
		//obj->getTransform()->rotation = Quaternion(obj->getTransform()->rotation.GetUp(), sin(e));
		//obj->getTransform()->position.SetX(sin(e));
		//scene->getCamera()->getTransform()->rotation = Quaternion(scene->getCamera()->getTransform()->rotation.GetRight(), sin(e));
	}
};
int main(){
	Engine* e = Engine::getInstance();
	e->initiate(new Display(800,600,"tr"),GraphicsHandle::OpenGL);
	Tu* app = new Tu();
	//e->setClearColor(vec3(0,0,0));
	e->start(app);

	return 0;
}
