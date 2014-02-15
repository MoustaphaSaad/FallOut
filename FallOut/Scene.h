#ifndef SCENE_H
#define SCENE_H
#include"GameObject.h"
#include"Camera.h"
class Scene:public GameObject{
public:
	Scene();
	~Scene();
	Camera* getCamera();
	void setCamera(Camera* val);
private:
	Camera* cam;
};
#endif