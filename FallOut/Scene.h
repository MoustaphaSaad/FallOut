#ifndef SCENE_H
#define SCENE_H
#include"GameObject.h"
#include"Camera.h"
class light;
class DirectionalLight;
class Scene:public GameObject{
	friend class RenderEngine;
public:
	Scene();
	~Scene();

	void Input();
	void Update();
	void Render();

	Camera* getCamera();
	void setCamera(Camera* val);

	void setClearColor(vec3 val);
	vec3 getClearColor();

	void addLight(light* val);
	light* getLight(int val);
	int getLightsCount();
	DirectionalLight* dirLight;
private:
	Camera* cam;
	vector<light*> ligths;
	vec3 clearColor;
};
#endif