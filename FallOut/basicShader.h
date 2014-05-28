#ifndef BASICSHADER_H
#define BASICSHADER_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
#include"DepthTexture.h"
class BasicShader:public Shader{
public:
	
	mat4 View,Projection;
	mat4 Model;

	BasicShader():Shader("basic","res/basic.glsl"){
	}
	~BasicShader(){
	}

	void Update(Transformable* obj){
		Scene* scene = Engine::getInstance()->getApplication()->getScene();
		View = Engine::getInstance()->getApplication()->getScene()->getCamera()->getPositionRotation();
		Projection = Engine::getInstance()->getApplication()->getScene()->getCamera()->getProjection();
		Model = obj->getTransform()->getModel();
		this->setUniform("View",View.Transpose());
		this->setUniform("Projection", Projection.Transpose());
		this->setUniform("Model",Model.Transpose());
		this->setUniform("shadowMatrix", Fallout::getRenderer()->getShadowMatrix().Transpose());
		this->setUniform("shadowTex", 1);

		Fallout::getRenderer()->getDepth()->bind(1);
		this->setUniform("LIGHTNUM",scene->getLightsCount());
		for(int i=0;i<scene->getLightsCount();i++){
			string text = "Lights[";
			text+=i+48;
			text+="]";
			this->setUniform(text+".pos",scene->getLight(i)->getPosition());
			this->setUniform(text+".la",scene->getLight(i)->getLa());
			this->setUniform(text+".ld",scene->getLight(i)->getLd());
			this->setUniform(text+".ls",scene->getLight(i)->getLs());
		}
		if (scene->dirLight != NULL){
			string name = "dirLight";
			this->setUniform(name + ".pos", scene->dirLight->getPosition());
			this->setUniform(name + ".la", scene->dirLight->getLa());
			this->setUniform(name + ".ld", scene->dirLight->getLd());
			this->setUniform(name + ".ls", scene->dirLight->getLs());
			this->setUniform(name + ".dir", scene->dirLight->getDirection());
		}

		this->setUniform("Epos", scene->getCamera()->getTransform()->position);

	}

};
#endif