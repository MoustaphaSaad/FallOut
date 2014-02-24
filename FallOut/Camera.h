#ifndef CAMERA_H_
#define CAMERA_H_

#include"Math3D.h"

class Camera{
public:
	Camera(const vec3 pos = vec3(),const vec3 forw = vec3(0,0,1),const vec3 up = vec3(0,1,0));
	
	void move(const vec3 val);
	void rotateX(float val);
	void rotateY(float val);
	void rotateZ(float val);

	void roll(float val);
	void pitch(float val);
	void yaw(float val);

	mat4 getPositionRotation();
	virtual mat4 getProjection();

	vec3 getForward();
	vec3 getBack();
	vec3 getRight();
	vec3 getLeft();
	vec3 getUp();
	vec3 getDown();
	vec3 getPosition();

private:
	vec3 position;
	vec3 forward;
	vec3 up;
};

class PerspectiveCamera: public Camera{
public:
    PerspectiveCamera(const vec3 pos = vec3(0,0,0), const vec3 forward = vec3(0,0,1), const vec3 up = vec3(0,1,0),
                      float fov = ToRadians(45.0f), float zNear = 0.1f, float zFar = 1000.0f);

	mat4 getProjection();

	float getFOV();
	float getZNear();
	float getZFar();
private:
	float FOV,zNear,zFar;
};
#endif