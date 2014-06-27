#include"SimpleShader.h"
#include"Engine.h"
#include"Application.h"
#include"resource1.h"
using namespace Fallout;
ShadowShader::ShadowShader():Shader("simple", content){

}
void ShadowShader::Update(Transformable* obj){
	View = Light->getPositionRotation(Engine::getInstance()->getApplication()->getScene()->getCamera());
	Model = obj->getTransform()->getModel();
	int lim= Light->getShadow()->Radius;
	//int lim =  max(cube.GetX(),max(cube.GetY(),cube.GetZ()));
	vec3 pos = Engine::getInstance()->getApplication()->getScene()->getCamera()->getTransform()->position;
	//mat4 ortho = mat4().InitOrthographic(lim,-lim,lim,-lim,lim,-lim)*mat4().InitTranslation(pos);
	mat4 ortho = mat4().InitOrthographic(lim,-lim,lim,-lim,lim,-lim);
	this->setUniform("View",View.Transpose());
	this->setUniform("Projection", ortho.Transpose());
	this->setUniform("Model",Model.Transpose());
}
ShadowShader::~ShadowShader(){

}

const string ShadowShader::content =
	"#version 330\n"

	"attribute vec3 position;\n"
	"attribute vec3 normal;\n"
	"attribute vec3 color;\n"
	"attribute vec2 texCoord;\n"
	"attribute vec3 tangent;\n"

	"vuniform mat4 Projection;\n"
	"vuniform mat4 View;\n"
	"vuniform mat4 Model;\n"



	"void VSmain(){\n"
		"gl_Position = Projection*View*Model*vec4(position,1.0);\n"
	"}\n"

	"void FSmain(){\n"
		"float depth = gl_FragCoord.z;\n"
		"gl_FragColor = vec4(depth);\n"
	"}\n"
	;