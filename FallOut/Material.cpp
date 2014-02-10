#include"Material.h"
#include"Engine.h"
Material::Material(const string name):Resource(name,ResourceType::MATERIAL){
	
}
Material::~Material(){
	//delete shader;
}
