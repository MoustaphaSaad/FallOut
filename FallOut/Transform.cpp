#include"Transform.h"

Transform::Transform(const vec3 pos,const vec4 rot , const vec3 scal ){
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
	Matrix4f translation = Matrix4f::InitTranslation(position);
	Matrix4f ScaleM = Matrix4f::InitScale(scale);

	model = childModel * translation * rotation.ToMatrix() * ScaleM;
}
