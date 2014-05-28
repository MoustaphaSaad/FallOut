#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;

#include <res/light.glh>

varying vec3 Position;
varying vec3 Normal;
varying vec2 ftexCoord;
varying vec3 Color;
varying mat4 mf;

varying vec4 shadow_coord;
varying vec3 eye_coord;

vuniform mat4 View;
vuniform mat4 Projection;
vuniform mat4 Model;
vuniform mat4 shadowMatrix;

funiform DirLight dirLight;
funiform sampler2D Tex;
funiform sampler2DShadow shadowTex;
funiform vec3 Epos;

funiform lightInfo Lights[10];
funiform int LIGHTNUM;
funiform materialInfo Mat;


void VSmain()
{
	mf = Model;
	mat3 Nm = mat3(Model);
	Nm = inverse(Nm);
	Nm = transpose(Nm);
	Color = color;
	Position = vec3(Model*vec4(position,1));
	Normal = normalize(Nm*normal);
	ftexCoord = texCoord;
	shadow_coord = shadowMatrix*vec4(Position,1);
	eye_coord = vec3(View*vec4(position,1.0));
	gl_Position = Projection*View*Model*vec4(position,1.0);
}

void FSmain()
{
	//vec4 sh = shadow_coord/shadow_coord.w;
	//sh.z *= 0.999;
	float f = textureProj(shadowTex, shadow_coord);
	vec4 tl;
	tl = vec4(0);

	
	//Calc the lights
	for(int i=0;i<LIGHTNUM;i++){
		vec4 ith = vec4(calcLight(Lights[i],Position,normalize(Normal),Mat),1);
		tl+=ith;
	}
	//check if there's a texture
	vec4 texC = texture(Tex,ftexCoord);
	//if(texC.x > 0 && texC.y >0 && texC.z >0 && texC.w > 0)
		tl += texC;

	//Adding the lights
	if(Color.x != -1)
		tl = tl*vec4(Color,1);

	vec4 DirC= CalcDirLight(dirLight,Position,normalize(Normal),vec3(mf*vec4(Epos,1)),Mat);
	tl+=vec4((dirLight.la*Mat.ka),1);
	tl+=(f*DirC);




	gl_FragColor = vec4(clamp(tl,vec4(0,0,0,1),vec4(1,1,1,1)).xyz,1.0);


}
