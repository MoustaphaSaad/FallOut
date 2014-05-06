#ifndef MATERIALBASIC_H_
#define MATERIALBASIC_H_
#include"RenderEngine.h"
#include"Material.h"
class BasicMaterial:public Material{
	friend class RenderEngine;
public:
	BasicMaterial();
	~BasicMaterial();

	void setDiffuse(vec3 val);
	vec3 getDiffuse();

	void setAmbient(vec3 val);
	vec3 getAmbient();

	void setSpecular(vec3 val);
	vec3 getSpecular();

	void setShininess(float val);
	float getShininess();

	void setTexture(Texture* val);
	Texture* getTexture();

	void use();
	void use(Shader* shdr);
private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	Texture* Tex;
	float shine;
};
#endif