#ifndef MATERIAL_H
#define MATERIAL_H
#include"Resources.h"
#include"Math3D.h"
#include"Texture.h"
#include"VisualComposer.h"
#include<memory>
using namespace std;

namespace Fallout{
	typedef tr1::shared_ptr<Material> MaterialPtr;
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
	virtual bool hasNormalMap(){
		return false;
	}
protected :
	Shader* shader;
};
}
#endif