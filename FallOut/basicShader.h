#ifndef SHADER_H
#define SHADER_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
class BasicShader:public Shader{
public:
	
	mat4 View,Projection;
	mat4 Model;

	BasicShader():Shader("basic","res/basic.glsl"){
	}
	~BasicShader(){
	}

	void Update(Transformable* obj){
		Scene* scene = Engine::getEngine()->getApplication()->getScene();
		View = Engine::getEngine()->getApplication()->getScene()->getCamera()->getPositionRotation();
		Projection = Engine::getEngine()->getApplication()->getScene()->getCamera()->getProjection();
		Model = obj->getTransform()->getModel();
		this->setUniform("MVP",Projection*View*Model);
		this->setUniform("Model",Model);
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

	}

};
#endif