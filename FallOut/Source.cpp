//#include<iostream>
//#include"FallOut.h"
//#include<algorithm>
//#include<Windows.h>
//using namespace std;
//using namespace Fallout;
//class Tu : public Application{
//public:
//	GameObject* obj;
//	double e;
//	Mesh* eo;
//	light * lolo,*lolo2;
//	GameObject* monkey;
//	FrameBuffer* fb;
//	Tu():Application(){
//		e=0;
//	}
//	
//	void init(){
//		scene->setClearColor(vec3(0.392,0.584,0.929));
//		Time::setFrameLimit(20);
//		scene->getCamera()->addComponent("freeMove",new FreeMove());
//		scene->getCamera()->addComponent("freeLook",new FreeLook());
//		BasicShader* shoho = new BasicShader();
//		
//		eo =resourceManager->createMesh("moka","res/MinePlane.obj");
//		eo->setShader(shoho);
//
//
//
//		Mesh* m = ObjLoader::loadObj("res/sphere.obj");
//		m->setShader(shoho);
//
//		Mesh* mm = ObjLoader::loadObj("res/moksa.obj");
//		mm->setShader(shoho);
//
//		obj = new GameObject();
//		obj->addComponent("renderer",new DefaultRenderer(obj,eo));
//		obj->Composer->receiveShadow = false;
//		scene->addChild(obj);
//
//		obj = new GameObject();
//		obj->addComponent("renderer",new DefaultRenderer(obj,eo));
//		obj->getTransform()->position.SetX(40);
//
//		obj->getTransform()->position.SetY(5);
//		scene->addChild(obj);
//
//
//		GameObject* aobj = new GameObject();
//		aobj->addComponent("renderer",new DefaultRenderer(aobj,mm));
//		aobj->getTransform()->position.SetX(40);
//		aobj->getTransform()->position.SetY(7);
//		aobj->Composer->castShadow = true;
//		scene->addChild(aobj);
//
//		
//
//		monkey = new GameObject();
//		monkey->addComponent("renderer",new DefaultRenderer(monkey,m));
//		monkey->getTransform()->position.SetY(1);
//		monkey->Composer->castShadow = true;
//		scene->addChild(monkey);
//
//		scene->getCamera()->getTransform()->position = vec3(3,3,3);
//
//		Plane* p = new Plane();
//		scene->addChild(p);
//	}
//	void setupScene(){
//		this->scene->setClearColor(vec3(1,0,0));
//		light* l = new light();
//		scene->addLight(l);
//		l = new light();
//		l->setPosition(vec3(0,10,0));
//		l->setLa(vec3(.5,.5,.5));
//	
//		scene->addLight(l);
//
//		l = new light();
//		l->setPosition(vec3(5, 1, 0));
//		l->setLd(vec3(1, .5, .5));
//		scene->addLight(l);
//		lolo = l;
//
//		l = new light();
//		l->setPosition(vec3(1, 0, 0));
//		l->setLa(vec3(.5,.25,.1));
//		l->setLd(vec3(.9,.75,.3));
//		scene->addLight(l);
//		l->setIntensity(2);
//		lolo2 = l;
//
//		DirectionalLight* ldir = new DirectionalLight(vec3(3, 1, 0), vec3(0, 0, 0),Shadow::Quality::Single,vec3(.5,.25,.1),vec3(.9,.75	,.3));
//		ldir->setIntensity(2);
//
//		scene->addDirLight(ldir);
//
//		DirectionalLight* ldir2 = new DirectionalLight(vec3(-3, 3, -3), vec3(0, 0, 0),Shadow::Quality::Single,vec3(.5,.5,.5),vec3(.8,.8,.8));
//		ldir2->setIntensity(1);
//
//		delete ldir2;
//		scene->addDirLight(ldir2);
//
//		scene->addDirLight(new DirectionalLight(vec3(-3,3, -3), vec3(0, 0, 0),vec3(.5,.5,.5),vec3(.9,.3,.3)));
//	}
//	void input(){
//		if(this->Input->getMouseButton(InputManager::Mouse::Right)==keyState::DOWN)
//			cout<<"weijf"<<endl;
//		if (Input->getKey(InputManager::Keys::KEY_x) == keyState::DOWN){
//			if (Time::getType() == Time::FPS::LIMITED)
//				Time::setType(Time::FPS::UNLIMITED);
//			else
//				Time::setType(Time::FPS::LIMITED);
//		}
//		if (Input->getKey(InputManager::Keys::KEY_3) == keyState::DOWN)
//			Time::setFrameLimit(10);
//	}
//	void update(TimeStep gameTime){
//		vec4 newRot = monkey->getTransform()->getLookAtRot(scene->getCamera()->getTransform()->position, vec3(0,1,0));
//		auto finale = monkey->getTransform()->rotation.Lerp(newRot, Time::getDelta()*10);
//		monkey->getTransform()->rotation = vec4(finale);
//	}
//	void postRender(){
//		e+=Time::getDelta();
//		lolo->setPosition(vec3(cos(e)*5,1,sin(e)*4));
//		lolo2->setPosition(vec3(sin(e)*5, 1, cos(e) * 4));
//		monkey->getTransform()->position.SetX(sin(e));
//	}
//};
//
//int main(){
//	Engine* e = Engine::getInstance();
//	e->initiate(new Display(800,600,"Test"),Engine::GraphicsHandle::OpenGL);
//	Tu* app = new Tu();
//	e->start(app);
//	return 0;
//}
