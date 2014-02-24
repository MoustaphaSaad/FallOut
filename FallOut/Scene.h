#ifndef SCENE_H
#define SCENE_H
#include"GameObject.h"
#include"Camera.h"
class Scene:public GameObject{
	friend class RenderEngine;
public:
	Scene();
	~Scene();

	Camera* getCamera();
	void setCamera(Camera* val);

	void setClearColor(vec3 val);
	vec3 getClearColor();
private:
	Camera* cam;
	vec3 clearColor;
};
#endif