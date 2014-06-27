#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
#include"DepthTexture.h"
#include"Light.h"
#include<string>
using namespace std;
namespace Fallout{
class ShadowShader :public Shader{
	const static string content;
public:

	mat4 View, Projection;
	mat4 Model;
	light* Light;

	ShadowShader();
	~ShadowShader();

	void Update(Transformable* obj);
};
}
#endif