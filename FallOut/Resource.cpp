#include"Resource.h"
#include"Engine.h"
using namespace Fallout;
Resource::Resource(const string name,Resource::Type t){
		this->name = name;
		this->type = t;
		ResourceManager::getInstance()->RegisterResource(this);
}
Resource::Resource(){
	this->name = "";
	this->type = Resource::Type::UNDEFINED;
}
Resource::~Resource(){
}
string Resource::getName(){
	return name;
}
Resource::Type Resource::getType(){
	return type;
}

void Resource::setName(string val){
	this->name = val;
}
void Resource::setType(Resource::Type val){
	this->type = val;
}