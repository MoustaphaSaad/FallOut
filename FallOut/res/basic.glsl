#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;

#include <res/light.glh>

varying vec3 Position;
varying vec3 Normal;
varying vec2 ftexCoord;

vuniform mat4 MVP;
vuniform mat4 Model;

funiform sampler2D Tex;


void VSmain()
{
	mat3 Nm = mat3(Model);
	Nm = inverse(Nm);
	Nm = transpose(Nm);
	Position = vec3(Model*vec4(position,1));
	Normal = normalize(Nm*normal);
	ftexCoord = texCoord;
	gl_Position = MVP*vec4(position,1.0);
}

void FSmain()
{
	vec4 tl = vec4(0);
	for(int i=0;i<LIGHTNUM;i++){
		vec4 ith = vec4(calcLight(i,Position,normalize(Normal)),1);
		tl+=ith;
	}
	vec4 texC = texture(Tex,ftexCoord);
	if(texC.x > 0 && texC.y >0 && texC.z >0 && texC.w > 0)
		tl *= texC;
	if(gl_FrontFacing){
		gl_FragColor = tl;
	}else{
		gl_FragColor = tl;
	}


}
