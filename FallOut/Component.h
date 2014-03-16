#ifndef COMPONENT_H
#define COMPONENT_H
#include<iostream>
#include"VisualObject.h"
class Updatable{

public:
	virtual void Input(){}
	virtual void Update(){}

};
class Renderable{

public:
	virtual void Render(){}
};
#endif