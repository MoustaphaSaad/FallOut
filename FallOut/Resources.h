#ifndef RESOURCES_H
#define RESOURCES_H
#include<string>
#include"Resource.h"
#include<map>
using namespace std;

class Mesh;
class Geometry;
class Material;
class Texture;
class Shader;

class ResourceManager{
public:
	ResourceManager(){
		ResourcesList = map<string,Resource*>();
	}

	Mesh* createMesh(const string name,const string fileName);
	Mesh* createMesh(const string name,Geometry* geo,Material* mat);
	Texture* createTexture(const string name,const string fileName);
	Texture* createTexture(const string name,int w,int h,unsigned char* data);
	Shader* createShader(const string name,const string fileName);
	void DeleteAll();
	void Delete(const string name);
	bool isExist(const string name);
	Resource* getResource(const string name);

	void RegisterResource(Resource* r);
	~ResourceManager(){
	}
	static ResourceManager* getInstance(){
		if(resourceManager == NULL){
			resourceManager = new ResourceManager();
		}
		return resourceManager;
	}
private:
	map<string,Resource*> ResourcesList;
	static ResourceManager* resourceManager;
};
#endif