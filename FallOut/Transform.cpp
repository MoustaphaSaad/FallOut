#include"Transform.h"

Transform::Transform(const vec3 pos,const vec3 rot , const vec3 scal ){
	this->position = pos;
	this->rotation = rot;
	this->scale = scal;
	model = mat4();
	MVP = mat4();
	childModel = mat4();
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

void Transform::setChildModel(const mat4 childModel){
	this->childModel = childModel;
}
void Transform::CalcModel()
{
	mat4 translation = mat4::InitTranslation(position);
	mat4 ScaleM = mat4::InitScale(scale);
	mat4 rot = mat4::InitRotation(rotation);

	model = childModel* translation * rot * ScaleM;
}
