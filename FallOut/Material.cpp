#include"Material.h"
#include"Engine.h"
Material::Material(const string name):Resource(name,ResourceType::MATERIAL){
	
}
Material::Material(const string name,Shader* s):Resource(name,ResourceType::MATERIAL){
	shader = s;
}
Material::~Material(){
	delete shader;
}

Shader* Material::getShader(){
	return shader;
}
void Material::setShader(Shader* shader){
	this->shader = shader;
}

int Material::getInt(string name){
	return IntMap[name];
}
float Material::getFloat(string name){
	return FloatMap[name];
}
vec3 Material::getVec3(string name){
	return Vec3Map[name];
}
mat4 Material::getMat4(string name){
	return Mat4Map[name];
}

void Material::addProperty(const string name,int val){
	IntMap[name] = val;
}
void Material::addProperty(const string name,float val){
	FloatMap[name] = val;
}
void Material::addProperty(const string name,vec3 val){
	Vec3Map[name] = val;
}
void Material::addProperty(const string name,mat4 val){
	Mat4Map[name] = val;
}