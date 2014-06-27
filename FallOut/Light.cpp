#include"Light.h"
#include<algorithm>
using namespace Fallout;
light::light(vec3 pos,vec3 la,vec3 ld,vec3 ls, float inten){
	transform->position = pos;
	La = la;
	Ld = ld;
	Ls = ls;
	intensity = inten;
	shadow = NULL;
}

vec3 light::getLa(){
	return La;
}

vec3 light::getLd(){
	return Ld;
}

vec3 light::getLs(){
	return Ls;
}

vec3 light::getPosition(){
	return transform->position;
}
float light::getIntensity(){
	return intensity;
}

void light::setPosition(vec3 val){
	transform->position = val;
}
void light::setLa(vec3 val){
	La = val;
}
void light::setLd(vec3 val){
	Ld = val;
}
void light::setLs(vec3 val){
	Ls = val;
}
void light::setIntensity(float val){
	intensity = min((float)10,val);
}

DirectionalLight::DirectionalLight(vec3 pos, vec3 dir,Shadow::Quality q, vec3 la, vec3 ld, vec3 ls):light(pos,la,ld,ls){
	transform->rotation = transform->getLookAtRot(dir, transform->rotation.GetUp());
	shadow = new Shadow(new ShadowShader(),q);
}
DirectionalLight::DirectionalLight(vec3 pos, vec3 dir,int q, vec3 la, vec3 ld, vec3 ls):light(pos,la,ld,ls){
	transform->rotation = transform->getLookAtRot(dir, transform->rotation.GetUp());
	shadow = new Shadow(new ShadowShader(),q);
}

vec3 DirectionalLight::getDirection(){
	return transform->rotation.GetForward();
}

void DirectionalLight::setDirection(vec3 dir){
	transform->rotation = transform->getLookAtRot(dir, transform->rotation.GetUp());
}

mat4 DirectionalLight::getPositionRotation(Camera* cam){

	
	Vector3f resultPos = cam->getTransform()->position + cam->getTransform()->rotation.GetForward() * shadow->Radius;
	Quaternion resultRot = transform->rotation;
	
	float worldTexelSize = (shadow->Radius*2)/((float)(1 << shadow->pow2));
	
	Vector3f lightSpaceCameraPos = resultPos.Rotate(resultRot.Conjugate());
	
	lightSpaceCameraPos.SetX(worldTexelSize * floor(lightSpaceCameraPos.GetX() / worldTexelSize));
	lightSpaceCameraPos.SetY(worldTexelSize * floor(lightSpaceCameraPos.GetY() / worldTexelSize));
	
	resultPos = lightSpaceCameraPos.Rotate(resultRot);
	
	return resultRot.Conjugate().ToRotationMatrix()*mat4().InitTranslation(resultPos*-1);
}