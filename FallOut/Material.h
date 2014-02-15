#ifndef MATERIAL_H
#define MATERIAL_H
#include"Resources.h"
#include"Math3D.h"
class Material:public Resource{
public:
	Material(const string);
	Material(const string,Shader* s);
	~Material();

	int getInt(string name);
	float getFloat(string name);
	vec3 getVec3(string name);
	mat4 getMat4(string name);

	void addProperty(const string name,int val);
	void addProperty(const string name,float val);
	void addProperty(const string name,vec3 val);
	void addProperty(const string name,mat4 val);
	
	Shader* getShader();
	void setShader(Shader* shader);
private :
	map<string,int> IntMap;
	map<string,float> FloatMap;
	map<string,vec3> Vec3Map;
	map<string,mat4> Mat4Map;
	Shader* shader;
};
#endif