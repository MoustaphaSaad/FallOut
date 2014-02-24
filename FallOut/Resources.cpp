#include"Resources.h"
#include"Texture.h"
#include"ObjLoader.h"
#include"Shader.h"
#include<iostream>
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

Resource* ResourceManager::getResource(const string name){
	if(isExist(name))
		return this->ResourcesList[name];
	return NULL;
}

Mesh* ResourceManager::createMesh(const string name,const string fileName){
	Mesh* obj;
	if(!isExist(name)){
		obj = ObjLoader::loadObj(name,fileName);
		RegisterResource(obj);
	}else{
		obj = (Mesh*)getResource(name);
	}
	return obj;
}
Mesh* ResourceManager::createMesh(const string name,Geometry* geo,Material* mat){
	Mesh* obj;
	if(!isExist(name)){
		obj = new Mesh(name,geo,mat);
		RegisterResource(obj);
	}else{
		obj = (Mesh*)getResource(name);
	}
	return obj;
}
Texture* ResourceManager::createTexture(const string name,const string fileName){
	Texture* obj;
	if(!isExist(name)){
		obj = new Texture(name,fileName);
		RegisterResource(obj);
	}else{
		obj = (Texture*)getResource(name);
	}
	return obj;
}
Texture* ResourceManager::createTexture(const string name,int w,int h,unsigned char* data){
	Texture* obj;
	if(!isExist(name)){
		obj = new Texture(name,w,h,data);
		RegisterResource(obj);
	}else{
		obj = (Texture*)getResource(name);
	}
	return obj;
}
Shader* ResourceManager::createShader(const string name,const string fileName){
	Shader* obj;
	if(!isExist(name)){
		obj = new Shader(name,fileName);
		RegisterResource(obj);
	}else{
		obj = (Shader*)getResource(name);
	}
	return obj;
}

Material* ResourceManager::createMaterial(const string name,Shader* shader){
	Material* obj;
	if(!isExist(name)){
		obj = new Material(name,shader);
		RegisterResource(obj);
	}else{
		obj= (Material*)getResource(name);
	}
	return obj;
}