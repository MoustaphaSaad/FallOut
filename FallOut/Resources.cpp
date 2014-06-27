#include"Resources.h"
#include"Texture.h"
#include"ObjLoader.h"
#include"Shader.h"
#include<iostream>
using namespace Fallout;
ResourceManager* ResourceManager::resourceManager = NULL;
void ResourceManager::RegisterResource(Resource* r){
	ResourcesList.insert(make_pair(r->getName(),r));
}

void ResourceManager::Delete(const std::string name)
{
	auto it = ResourcesList.find(name);
	if(it != ResourcesList.end()) 
	{
		delete it->second;
		ResourcesList.erase(it);
	} 
}
void ResourceManager::DeleteAll()
{
    for (auto it=ResourcesList.begin(); it!=ResourcesList.end(); ++it)
        delete it->second;
}

bool ResourceManager::isExist(const string name){
	if(this->ResourcesList.find(name) == ResourcesList.end())
		return false;
	return true;
}
template<class TYPE>
TYPE* ResourceManager::getResource(const string name){
	if(isExist(name))
		return (TYPE*)this->ResourcesList[name];
	return NULL;
}

Mesh* ResourceManager::createMesh(const string name,const string fileName){
	Mesh* obj;
	if(!isExist(name)){
		obj = ObjLoader::loadObj(fileName);
		obj->setType(Resource::MESH);
		obj->setName(name);
		RegisterResource(obj);
	}else{
		obj = getResource<Mesh>(name);
	}
	return obj;
}
Mesh* ResourceManager::createMesh(const string name,Geometry* geo,Material* mat){
	Mesh* obj;
	if(!isExist(name)){
		obj = new Mesh(name,geo,mat);
		RegisterResource(obj);
	}else{
		obj = getResource<Mesh>(name);
	}
	return obj;
}
Texture* ResourceManager::createTexture(const string name,const string fileName){
	Texture* obj;
	if(!isExist(name)){
		obj = new Texture(fileName);
		obj->setName(name);
		RegisterResource(obj);
	}else{
		obj = getResource<Texture>(name);
	}
	return obj;
}
Texture* ResourceManager::createTexture(const string name,int w,int h,unsigned char* data){
	Texture* obj;
	if(!isExist(name)){
		obj = new Texture(w,h,data);
		obj->setName(name);
		RegisterResource(obj);
	}else{
		obj = getResource<Texture>(name);
	}
	return obj;
}
Shader* ResourceManager::createShader(const string name,const string fileName){
	Shader* obj;
	if(!isExist(name)){
		obj = new Shader(name,fileName);
		RegisterResource(obj);
	}else{
		obj = getResource<Shader>(name);
	}
	return obj;
}

Material* ResourceManager::createMaterial(const string name,Shader* shader){
	Material* obj;
	if(!isExist(name)){
		obj = new Material(name,shader);
		RegisterResource(obj);
	}else{
		obj= getResource<Material>(name);
	}
	return obj;
}