#ifndef MATERIAL_H
#define MATERIAL_H
#include"Resources.h"
class Material:public Resource{
public:
	Material(const string);
	~Material();

	//Shader getShader();
	//void setShader(Shader shader);
private :
	//Shader* shader;
};
#endif