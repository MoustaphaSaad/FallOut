#include"Transform.h"
#include<iostream>
using namespace Fallout;
Transform::Transform(const vec3 pos,const vec4 rot , const vec3 scal ){
	this->position = pos;
	this->rotation = rot;
	this->scale = scal;
	model = mat4().InitIdentity();
	MVP = mat4().InitIdentity();
	parent = NULL;
}

mat4 Transform::getModel(bool calcModel){
	if(calcModel)
		CalcModel();

	return model;
}
mat4 Transform::getMVP(bool calcMVP, bool calcModel ){
	if(calcModel)
		CalcModel();
	if(calcMVP||calcModel)
		MVP = model;
	return MVP;
}

void Transform::setParentTransform(Transform* parentM){
	this->parent = parentM;
}
void Transform::CalcModel()
{
	mat4 translation = mat4().InitTranslation(position);
	mat4 ScaleM = mat4().InitScale(scale);

	mat4 parentMat = mat4().InitIdentity();

	if(parent!=NULL)
		parentMat = parent->getMVP();

	model = parentMat*translation * rotation.ToRotationMatrix() * ScaleM;
}
