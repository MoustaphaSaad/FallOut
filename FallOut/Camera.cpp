#include"Camera.h"
#include"Engine.h"
#include"ObjectBehavior.h"
#include"Timing.h"
Camera::Camera(){
	this->transform = new Transform();
}

void Camera::move(vec3 direction, float amt)
{
	transform->position = transform->position.Lerp((transform->position + (direction * amt)), Time::getDelta()*3);
}

mat4 Camera::getPositionRotation(){
	mat4 rotMat = transform->rotation.Conjugate().ToRotationMatrix();
	mat4 transMat;
	transMat.InitTranslation(transform->position*-1);
	mat4 res = rotMat * transMat;
	return res;
	//return transform->getModel();
}
mat4 Camera::getProjection(){
	return mat4();
}
void Camera::Input(){
	GameObject::Input();
}
void Camera::Update(TimeStep time){
	GameObject::Update(time);
}
void Camera::Render(){
	GameObject::Render();
}
PerspectiveCamera::PerspectiveCamera(const vec3 pos,const vec3 forward,const vec3 up,
									 float fov,float zNear,float zFar):Camera(){
	this->FOV = fov;
	this->zNear = zNear;
	this->zFar = zFar;
	
}

float PerspectiveCamera::getFOV(){
	return FOV;
}
float PerspectiveCamera::getZNear(){
	return zNear;
}
float PerspectiveCamera::getZFar(){
	return zFar;
}

mat4 PerspectiveCamera::getProjection(){
	return mat4().InitPerspective(FOV, Engine::getInstance()->getDisplay()->getAspect(), zNear, zFar);
}

void PerspectiveCamera::Input(){
	GameObject::Input();
}
void PerspectiveCamera::Update(TimeStep time){
	GameObject::Update(time);
}
void PerspectiveCamera::Render(){
	GameObject::Render();
}