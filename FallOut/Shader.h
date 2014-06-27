#ifndef SHADER_H
#define SHADER_H
#include"Transform.h"
#include"Engine.h"
#include"Resource.h"
#include"Material.h"
#include"GlobalStructs.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<memory>
using namespace std;
namespace Fallout{
	class Shader;
	typedef tr1::shared_ptr<Shader> ShaderPtr;
class Shader:public Resource{
public:
	
	Shader(const string fileName);
	Shader(const string name,const string fileName);
	virtual void Update(Transformable* obj, Material* mtl);
	void setUniform(string name,int val);
	void setUniform(string name,float val);
	void setUniform(string name,vec3 val);
	void setUniform(string name,mat4 val);
	void Bind();
	void BindTexture(Texture* txt,string sampler);
	static void unbind();
	~Shader();
	static string loadShader(const string fileName);
private:
	unsigned int m_Program;
	vector<unsigned int> m_Shaders;
	vector<UniformData> m_Uniforms;
	vector<ShaderStruct> m_Structs;
	map<string,int> Samplers;
	bool m_isValid;

	void handleSamplers();
};

}
#endif