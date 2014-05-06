#ifndef COMPONENT_H
#define COMPONENT_H
#include<iostream>
#include"VisualObject.h"
class Shader;
class Updatable{

public:
	virtual void Input(){}
	virtual void Update(){}

};
class Renderable{

public:
	virtual void Render(){}
	virtual void Render(Shader* shdr){}
};
#endif