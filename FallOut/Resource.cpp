#include"Resource.h"
#include"Engine.h"
Resource::Resource(const string name,ResourceType t){
		this->name = name;
		this->type = t;
}
Resource::~Resource(){
}
string Resource::getName(){
	return name;
}
ResourceType Resource::getType(){
	return type;
}