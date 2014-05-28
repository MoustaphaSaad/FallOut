#include"SimpleShader.h"
#include"Engine.h"
#include"Application.h"
SimpleShader::SimpleShader():Shader("simple", "res/simple.glsl"){

	}
	void SimpleShader::Update(Transformable* obj){
		View = Engine::getInstance()->getApplication()->getScene()->getCamera()->getPositionRotation();
		Projection = Engine::getInstance()->getApplication()->getScene()->getCamera()->getProjection();
		Model = obj->getTransform()->getModel();
		mat4 res = Projection*View*Model;
		int lim=15;
		mat4 ortho = mat4().InitOrthographic(lim,-lim,lim,-lim,0.1,-50);
		this->setUniform("View",View.Transpose());
		this->setUniform("Projection", ortho.Transpose());
		this->setUniform("Model",Model.Transpose());

	}