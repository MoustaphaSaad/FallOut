#ifndef SHADER_H_
#define SHADER_H_
#include"Transform.h"
#include"Engine.h"
#include"Resource.h"
#include"Material.h"
#include"GlobalStructs.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
using namespace std;
class Shader:public Resource{
public:
	Shader(const string name,const string fileName);
	void Update(Material material);
	void setUniform(string name,int val);
	void setUniform(string name,float val);
	void setUniform(string name,vec3 val);
	void setUniform(string name,mat4 val);
	void Bind();
	~Shader();

private:
	unsigned int m_Program;
	vector<unsigned int> m_Shaders;
	vector<UniformData> m_Uniforms;
	bool m_isValid;

	
	static string loadShader(const string fileName);
};
#endif