#include"Resource.h"
#include"Engine.h"
Resource::Resource(const string name,ResourceType t){
		this->name = name;
		this->type = t;
}
Resource::Resource(){
	this->name = "";
	this->type = ResourceType::UNDEFINED;
}
Resource::~Resource(){
}
string Resource::getName(){
	return name;
}
ResourceType Resource::getType(){
	return type;
}

void Resource::setName(string val){
	this->name = val;
}
void Resource::setType(ResourceType val){
	this->type = val;
}