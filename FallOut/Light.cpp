#include"Light.h"
light::light(vec3 pos,vec3 la,vec3 ld,vec3 ls){
	transform->position = pos;
	La = la;
	Ld = ld;
	Ls = ls;
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

DirectionalLight::DirectionalLight(vec3 pos, vec3 dir, vec3 la, vec3 ld, vec3 ls):light(pos,la,ld,ls){
	transform->rotation = transform->getLookAtRot(dir, transform->rotation.GetUp());
}

vec3 DirectionalLight::getDirection(){
	return transform->rotation.GetForward();
}

void DirectionalLight::setDirection(vec3 dir){
	transform->rotation = transform->getLookAtRot(dir, transform->rotation.GetUp());
}