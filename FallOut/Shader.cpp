#include"Shader.h"
#include <sstream>
#include <cassert>
#include <fstream>
#include<vector>
#include <iostream>
#include"StringOp.h"
#include"GLSLTranslator.h"
using namespace std;
using namespace Fallout;
Shader::Shader(const string content):Resource(){
	this->type = Resource::Type::SHADER;
	m_Program=0;
	m_isValid = false;
	m_Shaders = vector<unsigned int>();
	m_Uniforms = vector<UniformData>();
	Samplers = map<string,int>();

	string shaderText = content;
	m_Shaders.push_back(Engine::getInstance()->getGXManager()->CreateVertexShader(shaderText));
	m_Shaders.push_back(Engine::getInstance()->getGXManager()->CreateFragmentShader(shaderText));
	m_Program = Engine::getInstance()->getGXManager()->CreateProgram(&m_Shaders[0], m_Shaders.size());
	m_Structs = GLSL::CreateStructs(shaderText, m_Program);
	m_Uniforms = GLSL::CreateUniforms(shaderText, m_Program, m_Structs);
	handleSamplers();
}
Shader::Shader(const string name,const string content):Resource(name,Resource::Type::SHADER){
	m_Program=0;
	m_isValid = false;
	m_Shaders = vector<unsigned int>();
	m_Uniforms = vector<UniformData>();
	Samplers = map<string,int>();

	string shaderText = content;
	m_Shaders.push_back(Engine::getInstance()->getGXManager()->CreateVertexShader(shaderText));
	m_Shaders.push_back(Engine::getInstance()->getGXManager()->CreateFragmentShader(shaderText));
	m_Program = Engine::getInstance()->getGXManager()->CreateProgram(&m_Shaders[0], m_Shaders.size());
	m_Structs = GLSL::CreateStructs(shaderText, m_Program);
	m_Uniforms = GLSL::CreateUniforms(shaderText, m_Program, m_Structs);
	handleSamplers();
}
void Shader::handleSamplers(){
	int samplerID =0;
	for(int i=0;i<m_Uniforms.size();i++)
		if(StringOp::Contains(m_Uniforms[i].Type,"sampler")){
			this->Samplers[m_Uniforms[i].Name] = samplerID++;
		}
}
void Shader::BindTexture(Texture* txt,string sampler){
	setUniform(sampler,Samplers[sampler]);
	txt->bind(Samplers[sampler]);
}
Shader::~Shader(){
	Engine::getInstance()->getGXManager()->DeleteShader(m_Program, &m_Shaders[0], m_Shaders.size());
}

void Shader::Bind(){
	Engine::getInstance()->getGXManager()->BindShader(m_Program);
}

void Shader::Update(Transformable* obj,Material* mtl){


}

void Shader::setUniform(string name,int val){
	UniformData *uni = NULL;
	for(int i=0;i<m_Uniforms.size();i++){
		if(m_Uniforms[i].Name == name)
			uni = &m_Uniforms[i];
	}
	if(!uni){
		printf("Error Uniform %s doesn't Exist\n",name.c_str());
		return;
	}
	Engine::getInstance()->getGXManager()->setUniform(uni->Location, val);
}
void Shader::setUniform(string name,float val){
	UniformData *uni = NULL;
	for(int i=0;i<m_Uniforms.size();i++){
		if(m_Uniforms[i].Name == name)
			uni = &m_Uniforms[i];
	}
	if(!uni){
		printf("Error Uniform %s doesn't Exist\n",name.c_str());
		return;
	}
	Engine::getInstance()->getGXManager()->setUniform(uni->Location, val);
}
void Shader::setUniform(string name,vec3 val){
	UniformData *uni = NULL;
	for(int i=0;i<m_Uniforms.size();i++){
		if(m_Uniforms[i].Name == name)
			uni = &m_Uniforms[i];
	}
	if(!uni){
		printf("Error Uniform %s doesn't Exist\n",name.c_str());
		return;
	}
	Engine::getInstance()->getGXManager()->setUniform(uni->Location, val);
}
void Shader::setUniform(string name,mat4 val){
	UniformData *uni = NULL;
	for(int i=0;i<m_Uniforms.size();i++){
		if(m_Uniforms[i].Name == name)
			uni = &m_Uniforms[i];
	}
	if(!uni){
		printf("Error Uniform %s doesn't Exist\n",name.c_str());
		return;
	}
	Engine::getInstance()->getGXManager()->setUniform(uni->Location, val);
}

string Shader::loadShader(const string fileName){
	ifstream file;
	file.open(fileName.c_str());

	string output;
	string line;

	if(file.is_open()){
		while(file.good()){
			getline(file,line);
			if(line.find("#include") == string::npos)
				output.append(line + "\n");
			else{
				
				string includeFileName = StringOp::Split(line,'<')[1];
				includeFileName.pop_back();
				//includeFileName = includeFileName.substr(1,includeFileName.length() -2);

				string toAppend = loadShader(includeFileName);
				output.append(toAppend+"\n");
			}
		}
	}else{
		printf(("Unable to load shader: "+ fileName +"\n").c_str());
	}
	return output;
}

void Shader::unbind(){
	Engine::getInstance()->getGXManager()->BindShader(0);
}