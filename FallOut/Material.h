#ifndef MATERIAL_H
#define MATERIAL_H
#include"Resources.h"
#include"Math3D.h"
#include"Texture.h"
class Material:public Resource{
public:
	Material();
	Material(const string);
	Material(const string,Shader* s);
	~Material();

	virtual void use(){}
	virtual void use(Shader* shdr){}
	
	Shader* getShader();
	void setShader(Shader* shader);
protected :
	Shader* shader;
};
#endif