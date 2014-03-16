#include"Light.h"
light::light(vec3 pos,vec3 la,vec3 ld,vec3 ls){
	position = pos;
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
	return position;
}

void light::setPosition(vec3 val){
	position = val;
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