#include"Material.h"
#include"Engine.h"
Material::Material(const string name):Resource(name,ResourceType::MATERIAL){
	this->shader = NULL;
}
Material::Material(const string name,Shader* s):Resource(name,ResourceType::MATERIAL){
	shader = s;
}
Material::Material():Resource(){
	this->type = ResourceType::MATERIAL;
	this->shader = NULL;
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