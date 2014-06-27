#ifndef MATERIALBASIC_H_
#define MATERIALBASIC_H_
#include"RenderEngine.h"
#include"Material.h"
#include<memory>
using namespace std;
namespace Fallout{
	class BasicMaterial;
	typedef tr1::shared_ptr<BasicMaterial> BasicMaterialPtr;
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

	void setNormalTexture(Texture* val);
	Texture* getNormaleTexture();

	bool hasNormalMap(){
		if(NormalTex != NULL)
			return true;
		return false;
	}

	void use();
	void use(Shader* shdr);
private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	Texture* Tex;
	Texture* NormalTex;
	float shine;
};
}
#endif