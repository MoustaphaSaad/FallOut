#include<iostream>
#include"FallOut.h"
#include"Cloth.h"
using namespace std;
class CamBe : public ObjectBehavior{
	bool mouseLocked;
public:
	CamBe(){
		mouseLocked = false;
	}
	void Input(){
		Camera* cam = (Camera*)parent;
		float sensitivity = 0.005f;
		float movAmt = (float)(Time::getDelta()*10);
		float rotAmt = (float)(Time::getDelta());

		if(input->getKey(27)==keyState::DOWN){
			mouseLocked=false;
		}
		
		if(mouseLocked){
			float CX = Engine::getEngine()->getDisplay()->width / 2;
			float CY = Engine::getEngine()->getDisplay()->height/ 2;
			vec2 centerPosition = vec2(CX,CY);
			vec2 deltaPos = input->getMousePosition() - centerPosition;

			bool rotY = deltaPos.GetX() !=0;
			bool rotX = deltaPos.GetY() !=0;

			if(rotY)
				cam->rotateY(deltaPos.GetX()*sensitivity);
			if(rotX)
				cam->rotateX(deltaPos.GetY()*sensitivity);
			if(rotX||rotY)
				input->setMousePosition(centerPosition);
		}

		if(input->getMouseButton(0)==keyState::DOWN){
			float CX = Engine::getEngine()->getDisplay()->width / 2;
			float CY = Engine::getEngine()->getDisplay()->height/ 2;
			vec2 centerPosition = vec2(CX,CY);
			input->setMousePosition(centerPosition);
			mouseLocked = true;
		}

		if(input->getKey('w')==keyState::DOWN){
			vec3 val = cam->getForward();
			val*=movAmt;
			cam->move(val);
		}
		if(input->getKey('s')==keyState::DOWN){
			vec3 val = cam->getForward();
			val*=-movAmt;
			cam->move(val);
		}
		if(input->getKey('a')==keyState::DOWN){
			vec3 val = cam->getLeft();
			val*=movAmt;
			cam->move(val);
		}
		if(input->getKey('d')==keyState::DOWN){
			vec3 val = cam->getRight();
			val*=movAmt;
			cam->move(val);
		}
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
		obj->getTransform()->scale.SetX(.1);
		//scene->addChild(obj);

		Cloth* cl = new Cloth(3, 3, 20, 20);
		cl->getTransform()->position.SetY(3);
		cl->getTransform()->position.SetZ(10);
		cl->getTransform()->position.SetX(-2);
		scene->addChild(cl);

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
		if (this->Input->getKey('m') == keyState::DOWN){
			Mesh*moka = ObjLoader::loadObj("koko","res/MultiO.obj" );
			eo->updateGeometry(moka->getGeometry());
		}
	}
	void postRender(){
		e+=Time::getDelta();
		obj->getTransform()->rotation.SetY((sin(e)*180));
		obj->getTransform()->position.SetX(sin(e));
		//scene->getCamera()->pitch(sin(e));
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
