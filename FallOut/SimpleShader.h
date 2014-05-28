#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H
#include"Shader.h"
#include"Camera.h"
#include"Application.h"
#include"DepthTexture.h"
class SimpleShader :public Shader{
public:

	mat4 View, Projection;
	mat4 Model;

	SimpleShader();
	~SimpleShader();

	void Update(Transformable* obj);

};
#endif