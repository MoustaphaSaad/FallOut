#ifndef CAMERA_H_
#define CAMERA_H_

#include"Math3D.h"
#include"Component.h"
#include"GameObject.h"

class Camera:public GameObject{
	friend class Scene;
public:
	Camera();
	
	void move(const vec3 dir,float val);

	virtual void Input();
	virtual void Update(TimeStep time);
	virtual void Render();

	mat4 getPositionRotation();
	virtual mat4 getProjection();
	virtual mat4 getProjection(float aspect){
		return mat4().InitIdentity();
	}


private:
};

class PerspectiveCamera: public Camera{
public:
    PerspectiveCamera(const vec3 pos = vec3(0,0,0), const vec3 forward = vec3(0,0,1), const vec3 up = vec3(0,1,0),
                      float fov = ToRadians(45.0f), float zNear = 1.0f, float zFar = 100.0f);

	void Input();
	void Update(TimeStep time);
	void Render();


	mat4 getProjection();

	float getFOV();
	float getZNear();
	float getZFar();
private:
	float FOV,zNear,zFar;
};
#endif