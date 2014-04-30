#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"Math3D.h"

class Transform{
public:
	vec3 position;
	vec4 rotation;
	vec3 scale;

	Transform(const vec3 pos = vec3(0,0,0),const vec4 rot = vec4(0,0,0,1), const vec3 scal = vec3(1,1,1));

	mat4 getModel(bool calcModel=true);
	mat4 getMVP(bool calcMVP = true, bool calcModel = true);
	void Transform::Rotate(const Vector3f& axis, float angle)
	{
		rotation = Quaternion((Quaternion(axis, angle) * rotation).Normalized());
	}
	void setChildModel(const mat4 childModel);

private:
	mat4 model,MVP,childModel;
	void CalcModel();
};
#endif