#include"Camera.h"
#include"Engine.h"

Camera::Camera(const vec3 pos,const vec3 forward,const vec3 up){
	this->position = pos;
	this->forward = forward.Normalized();
	this->up = up.Normalized();
}

void Camera::move(const vec3 val){
	this->position += val;
}

void Camera::rotateX(float val){
	this->forward = forward.Rotate(vec3::RIGHT,val).Normalized();
	up = up.Rotate(vec3::RIGHT,val).Normalized();
}

void Camera::rotateY(float val){
	forward = forward.Rotate(vec3::UP,val).Normalized();
	up = up.Rotate(vec3::UP,val).Normalized();
}

void Camera::rotateZ(float val){
	forward = forward.Rotate(vec3::FORWARD,val).Normalized();
	up = up.Rotate(vec3::FORWARD,val).Normalized();
}

void Camera::roll(float val){
	up = up.Rotate(forward,val).Normalized();
}

void Camera::pitch(float val){
	vec3 right = up.Cross(forward).Normalized();

	forward = forward.Rotate(right,val).Normalized();
	up = forward.Cross(right).Normalized();
}

void Camera::yaw(float val)
{
	forward = forward.Rotate(up,val).Normalized();
}

mat4 Camera::getPositionRotation(){
	return mat4::InitLookTo(position*-1,forward,up);
}
mat4 Camera::getProjection(){
	return mat4();
}

vec3 Camera::getForward(){
	return forward;
}

vec3 Camera::getBack(){
	return up.Cross(forward).Normalized();
}

vec3 Camera::getRight()
{
	return up.Cross(forward).Normalized();
}

vec3 Camera::getLeft() 
{
	return forward.Cross(up).Normalized();
}

vec3 Camera::getUp() 
{
	return up;
}

vec3 Camera::getDown() 
{
	return up * -1;
}

vec3 Camera::getPosition()
{
	return position;
}

PerspectiveCamera::PerspectiveCamera(const vec3 pos,const vec3 forward,const vec3 up,
									 float fov,float zNear,float zFar):Camera(pos,forward,up){
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
	return mat4::InitPerspective(FOV,Engine::getEngine()->getDisplay()->getAspect(),zNear,zFar);
}