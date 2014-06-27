#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"Math3D.h"
#include"Timing.h"
#include<memory>
using namespace std;
namespace Fallout{
	class Transform;
	typedef tr1::shared_ptr<Transform> TransformPtr;
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
	void move(const vec3 dir,float val){
		position = position.Lerp((position + (dir * val)), Time::getDelta()*3);
	}
	vec4 Transform::getLookAtRot(vec3 point, vec3 up){
		return vec4(mat4().InitRotationFromDirection((point - position).Normalized(), up).Transpose());
	}
	void setParentTransform(Transform* childModel);

private:
	mat4 model,MVP;
	Transform* parent;
	void CalcModel();
};
}
#endif