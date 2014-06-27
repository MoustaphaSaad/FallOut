#ifndef SCENE_H
#define SCENE_H
#include"GameObject.h"
#include"Camera.h"
#include<memory>
using namespace std;
namespace Fallout{
	class Scene;
	typedef tr1::shared_ptr<Scene> ScenePtr;
class light;
class DirectionalLight;
struct TimeStep;
class Scene:public GameObject{
	friend class RenderEngine;
public:

	Scene();
	~Scene();

	void Input();
	void Update(TimeStep time);
	void Render();

	Camera* getCamera();
	void setCamera(Camera* val);

	void setClearColor(vec3 val);
	vec3 getClearColor();

	void addLight(light* val);
	void addDirLight(DirectionalLight* val);
	DirectionalLight* getDirLight(int val);
	int getDirLightsCount(){
		return DirLights.size();
	}
	light* getLight(int val);
	int getLightsCount();
protected:
	Camera* cam;
	vector<light*> ligths;
	vector<DirectionalLight*> DirLights;
	vec3 clearColor;
};
}
#endif