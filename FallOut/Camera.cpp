#include"Camera.h"
#include"Engine.h"
#include"ObjectBehavior.h"

Camera::Camera(){
	this->transform = new Transform();
	camComp=NULL;
}

void Camera::move(vec3 direction, float amt)
{
	transform->position = (transform->position + (direction * amt));
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

Updatable* Camera::getCamComp(){
	return camComp;
}
void Camera::setCamComp(Updatable* val){
	ObjectBehavior* obj = (ObjectBehavior*)val;
	obj->setParent(this);
	camComp = val;
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