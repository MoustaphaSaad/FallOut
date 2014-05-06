#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
class SimpleShader :public Shader{
public:

	mat4 View, Projection;
	mat4 Model;

	SimpleShader() :Shader("simple", "res/simple.glsl"){
	}
	~SimpleShader(){
	}

	void Update(Transformable* obj){
		Scene* scene = Engine::getInstance()->getApplication()->getScene();
		View = Engine::getInstance()->getApplication()->getScene()->getCamera()->getPositionRotation();
		Projection = Engine::getInstance()->getApplication()->getScene()->getCamera()->getProjection();
		Model = obj->getTransform()->getModel();
		mat4 res = Projection*View*Model;
		this->setUniform("MVP", res.Transpose());

	}

};
#endif