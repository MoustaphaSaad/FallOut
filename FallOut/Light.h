#ifndef LIGHT_H
#define LIGHT_H
#include"Math3D.h"
#include"VisualObject.h"
class light:public Transformable{
protected:
	vec3 La,Ld,Ls;
public:
	light(vec3 pos=vec3(0,0,0),vec3 la=vec3(.5,.5,.5),vec3 ld=vec3(1,1,1),vec3 ls=vec3(1,1,1));

	vec3 getPosition();
	vec3 getLa();
	vec3 getLd();
	vec3 getLs();
	
	void setPosition(vec3 val);
	void setLa(vec3 val);
	void setLd(vec3 val);
	void setLs(vec3 val);
};

class DirectionalLight:public light{
public:
	DirectionalLight(vec3 pos = vec3(0, 0, 0),vec3 dir=vec3(0,0,0), vec3 la = vec3(.5, .5, .5), vec3 ld = vec3(.1, .1, .1), vec3 ls = vec3(.1, .1, .1));

	vec3 getDirection();

	void setDirection(vec3 dir);
};
#endif