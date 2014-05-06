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
		float movAmt = (float)(Time::getDelta()*10);
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
	light * lolo,*lolo2;
	GameObject* monkey;
	Tu():Application(){
		e=0;
	}
	
	void init(){
		

		scene->getCamera()->setCamComp(new CamBe());
		Shader* shoho = new BasicShader();
		
		eo =resourceManager->createMesh("moka","res/Plane.obj");
		eo->getMaterial()->setShader(shoho);
		for(int i=0;i<eo->getSubMeshCount();i++){
			eo->getSubMesh(i)->getMaterial()->setShader(shoho);
		}
		obj = new GameObject(new Transform());
		obj->setRenderComponent(new ObjectRenderer(eo));
		//obj->getTransform()->position.SetZ(10);
		//obj->getTransform()->scale.SetX(.1);
		scene->addChild(obj);

		Mesh* m = ObjLoader::loadObj("moksa", "res/BlankMonkey.obj");
		m->getMaterial()->setShader(shoho);
		for (int i = 0; i<m->getSubMeshCount(); i++){
			m->getSubMesh(i)->getMaterial()->setShader(shoho);
		}
		GameObject* aobj = new GameObject(new Transform());
		aobj->setRenderComponent(new ObjectRenderer(m));
		aobj->getTransform()->position.SetX(3);
		aobj->getTransform()->position.SetY(2);
		scene->addChild(aobj);

		monkey = new GameObject();
		monkey->setRenderComponent(new ObjectRenderer(m));
		monkey->getTransform()->position.SetY(1);
		scene->addChild(monkey);

		Cloth* cl = new Cloth(3, 3, 10, 10);
		cl->getTransform()->position.SetY(3);
		cl->getTransform()->position.SetZ(3);
		cl->getTransform()->position.SetX(-2);
		scene->addChild(cl);
		//Atmosphere* at = new Atmosphere();
		//scene->addChild(at);

		//scene->getCamera()->getTransform()->Rotate(vec3(1, 0, 0), .5);
		scene->getCamera()->getTransform()->position.SetX(15);
		scene->getCamera()->getTransform()->position.SetY(15);
	}
	void setupScene(){
		light* l = new light();
		//scene->addLight(l);
		l = new light();
		l->setPosition(vec3(0,10,0));
		l->setLa(vec3(.5,.5,.5));
	
		//scene->addLight(l);

		l = new light();
		l->setPosition(vec3(5, 1, 0));
		l->setLd(vec3(1, .5, .5));
		//scene->addLight(l);
		lolo = l;

		l = new light();
		l->setPosition(vec3(-5, 1, 0));
		l->setLd(vec3(.5, .5, 1));
		//scene->addLight(l);
		lolo2 = l;

		scene->dirLight = new DirectionalLight(vec3(15, 15, 0), vec3(0, 0, 0),vec3(1,1,1),vec3(.75,.75,.75));
	}
	void input(){
		if(this->Input->getKey(27)==keyState::DOWN)
			cout<<"weijf"<<endl;
	}
	void update(){
		
		vec4 newRot = monkey->getTransform()->getLookAtRot(scene->getCamera()->getTransform()->position, vec3(0,1,0));
		auto finale = monkey->getTransform()->rotation.Lerp(newRot, Time::getDelta());
		monkey->getTransform()->rotation = vec4(finale);
	}
	void postRender(){
		e+=Time::getDelta();
		lolo->setPosition(vec3(cos(e)*5,1,sin(e)*4));
		lolo2->setPosition(vec3(sin(e)*5, 1, cos(e) * 4));
		//obj->getTransform()->rotation = Quaternion(obj->getTransform()->rotation.GetUp(), sin(e));
		monkey->getTransform()->position.SetX(sin(e));
		//scene->getCamera()->getTransform()->rotation = Quaternion(scene->getCamera()->getTransform()->rotation.GetRight(), sin(e));
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, Fallout::getEngine()->rtexs);
		//eo->getMaterial()->getShader()->setUniform("Tex", 1);
		//obj->Render();
		//glBindTexture(GL_TEXTURE_2D, 0);
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
