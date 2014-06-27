#ifndef BASICSHADER_H
#define BASICSHADER_H
#include"Shader.h"
#include"Resource.h"
#include<memory>
namespace Fallout{
	class BasicShader;
	typedef tr1::shared_ptr<BasicShader> BasicShaderPtr;
class BasicShader:public Shader{
private:
	const static string content;
public:
	float fogStart,fogEnd;
	bool fogEnabled;
	vec3 fogColor;
	mat4 View,Projection;
	mat4 Model;

	BasicShader():Shader("basic",content){
		fogStart=1;
		fogEnd = 10;
		fogEnabled = false;
		fogColor = vec3(1,1,1);
	}
	~BasicShader(){
		Shader::~Shader();
	}

	void Update(Transformable* obj,Material* mtl);

};


}
#endif