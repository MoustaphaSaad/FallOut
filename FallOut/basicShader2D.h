#ifndef BASICSHADER2D_H
#define BASICSHADER2D_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
class BasicShader2D :public Shader{
public:

	mat4 View, Projection;
	mat4 Model;

	BasicShader2D() :Shader("res/basic2D.glsl"){
		this->setName("BasicShader2D");
		ResourceManager::getInstance()->AddResource(this);
	}
	~BasicShader2D(){
	}

	void Update(Transformable* obj){
		
	}

};
#endif