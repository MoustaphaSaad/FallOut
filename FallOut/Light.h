#ifndef LIGHT_H
#define LIGHT_H
#include"Math3D.h"
#include"VisualObject.h"
#include"FrameBuffer.h"
#include"SimpleShader.h"
#include<memory>
using namespace std;
namespace Fallout{
	class DirectionalLight;
	class light;
	class Shadow;
	typedef tr1::shared_ptr<DirectionalLight> DirectionalLightPtr;
	typedef tr1::shared_ptr<light> lightPtr;
	typedef tr1::shared_ptr<Shadow> ShadowPtr;
class Shadow{
	friend class light;
	friend class DirectionalLight;
	friend class RenderEngine;
	void init(){
		if(quality == Quality::Single)
			ShadowBuffer = new FrameBuffer(1024,1024);
		else if (quality == Quality::Double)
			ShadowBuffer = new FrameBuffer(1024*2,1024*2);
		else if (quality == Quality::Half)
			ShadowBuffer = new FrameBuffer(1024/2,1024/2);
		else
			ShadowBuffer = new FrameBuffer(pow(2,pow2),pow(2,pow2));
	}
public:

	enum Quality{Double,Single,Half};

	FrameBuffer* ShadowBuffer;
	mat4 shadowMatrix;
	Shader* shadowShader;
	Quality quality;
	double Radius;
	int pow2;
	float softness;
	Shadow(Shader* renderShader,Quality q = Quality::Single,double R=20){
		quality = q;
		if(q==Quality::Single)
			pow2 = 10;
		else if(q==Quality::Double)
			pow2 = 11;
		else if(q==Quality::Half)
			pow2 = 9;
		shadowShader = renderShader;
		shadowMatrix = mat4().InitIdentity();
		Radius = R;
		softness = 1;
		init();
	}
	Shadow(Shader* renderShader,int q = 10,double R=20){
		pow2=q;
		shadowShader = renderShader;
		shadowMatrix = mat4().InitIdentity();
		Radius = R;
		softness = 1;
		init();
	}
	~Shadow(){
		if(shadowShader!=NULL){
			delete shadowShader;
		}
		if(ShadowBuffer!=NULL)
			delete ShadowBuffer;
	}
};
class light:public Transformable{
	friend class RenderEngine;
protected:
	vec3 La,Ld,Ls;
	float intensity;
	Shadow* shadow;
public:

	light(vec3 pos=vec3(0,0,0),vec3 la=vec3(.5,.5,.5),vec3 ld=vec3(0.75,0.75,0.75),vec3 ls=vec3(.5,.5,.5),float inten = 1);
	~light(){
		if(shadow!=NULL)
			delete shadow;
	}
	vec3 getPosition();
	vec3 getLa();
	vec3 getLd();
	vec3 getLs();
	float getIntensity();
	virtual mat4 getPositionRotation(Camera* cam){return mat4().InitIdentity();}
	Shadow* getShadow(){

		return shadow;
	}
	mat4 getShadowMatrix(){
		return shadow->shadowMatrix;
	}
	void setPosition(vec3 val);
	void setLa(vec3 val);
	void setLd(vec3 val);
	void setLs(vec3 val);
	void setIntensity(float val);
};

class DirectionalLight:public light{
	friend class RenderEngine;
public:

	DirectionalLight(vec3 pos = vec3(0, 0, 0),vec3 dir=vec3(0,0,0),Shadow::Quality q=Shadow::Quality::Single, vec3 la = vec3(.5, .5, .5), vec3 ld = vec3(.75, .75, .75), vec3 ls = vec3(.5, .5, .5));
	DirectionalLight(vec3 pos = vec3(0, 0, 0),vec3 dir=vec3(0,0,0),int q =10, vec3 la = vec3(.5, .5, .5), vec3 ld = vec3(.75, .75, .75), vec3 ls = vec3(.5, .5, .5));
	~DirectionalLight(){

	}
	vec3 getDirection();

	mat4 getPositionRotation(Camera* cam);
	void setDirection(vec3 dir);
};

}
#endif