#include"MaterialBasic.h"
#include"basicShader.h"
using namespace Fallout;
BasicMaterial::BasicMaterial(){
	ambient = vec3(.1,.1,.1);
	diffuse = vec3(.80,.8,.8);
	specular = vec3(.9,.9,.9);
	shine = .65;
	Tex = NULL;
	NormalTex = NULL;
	shader = new BasicShader();
}
BasicMaterial::~BasicMaterial(){
}

void BasicMaterial::setDiffuse(vec3 val){
	diffuse = val;
}
vec3 BasicMaterial::getDiffuse(){
	return diffuse;
}

void BasicMaterial::setAmbient(vec3 val){
	ambient = val;
}
vec3 BasicMaterial::getAmbient(){
	return ambient;
}

void BasicMaterial::setSpecular(vec3 val){
	specular = val;
}
vec3 BasicMaterial::getSpecular(){
	return specular;
}

void BasicMaterial::setShininess(float val){
	shine = val;
}
float BasicMaterial::getShininess(){
	return shine;
}

Texture* BasicMaterial::getTexture(){
	return Tex;
}
void BasicMaterial::setTexture(Texture* val){
	Tex = val;
}

void BasicMaterial::setNormalTexture(Texture* val){
	NormalTex = val;
}

Texture* BasicMaterial::getNormaleTexture(){
	return NormalTex;
}

void BasicMaterial::use(){
	shader->setUniform("Mat.ka",ambient);
	shader->setUniform("Mat.kd",diffuse);
	shader->setUniform("Mat.ks",specular);
	shader->setUniform("Mat.shine",shine);
	if(Tex!=NULL){
		shader->BindTexture(Tex,"Tex");
	}
	if(NormalTex != NULL){
		shader->BindTexture(NormalTex,"NormalTex");
	}
}

void BasicMaterial::use(Shader* shdr){
	shader->Bind();
}