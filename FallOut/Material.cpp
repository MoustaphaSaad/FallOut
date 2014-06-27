#include"Material.h"
#include"Engine.h"
#include"GameObject.h"
using namespace Fallout;
Material::Material(const string name):Resource(name,Resource::Type::MATERIAL){
	this->shader = NULL;
}
Material::Material(const string name,Shader* s):Resource(name,Resource::Type::MATERIAL){
	shader = s;
}
Material::Material():Resource(){
	this->type = Resource::Type::MATERIAL;
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