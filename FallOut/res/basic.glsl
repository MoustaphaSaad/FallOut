#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;
attribute vec3 tangent;

struct lightInfo{
	vec3 pos;
	vec3 la;
	vec3 ld;
	vec3 ls;
	float intensity;
};
struct DirLight{
	vec3 pos;
	vec3 dir;
	vec3 la;
	vec3 ld;
	vec3 ls;
	float intensity;
	mat4 shadowMatrix;
};
struct materialInfo{
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float shine;
};
struct lightOut{
	vec3 la;
	vec3 ld;
	vec3 ls;
};
fragment lightOut calcLight(lightInfo light,vec3 pos,vec3 norm,materialInfo Mat){
	lightOut res;
	vec3 lpos = light.pos;
	float dist = length(pos-lpos);
	float att = 1.0/(1.0+0.01*dist+0.001*dist*dist);
	vec3 ambient = Mat.ka*light.la;

	vec3 surf2light=normalize(lpos-pos);
	vec3 N = normalize(norm);
	float dcont = max(0.0,dot(N,surf2light));
	vec3 diffuse=dcont*(Mat.kd*light.ld);

	vec3 surf2view=normalize(-pos);
	vec3 reflection = reflect(-surf2light,N);

	float scont = pow(max(0.0,dot(surf2view,-reflection)),Mat.shine);
	vec3 specular = scont*light.ls*Mat.ks;

	res.la = ambient*att*light.intensity;
	res.ld = diffuse*att*light.intensity;
	res.ls = specular*att*light.intensity;

	return res;
}

fragment lightOut CalcDirLight(DirLight light,vec3 pos,vec3 normal,vec3 epos,materialInfo Mat){
	lightOut res;

	float df = dot(normal,-light.dir);

	vec4 dc = vec4(0,0,0,0);
	vec4 ds = vec4(0,0,0,0);

	if(df>0){
		dc = vec4(light.ld,1.0)*df*vec4(Mat.kd,1.0);
		vec3 dirToE = normalize(epos - pos);
		vec3 hd = normalize(dirToE - light.dir);

		float sf = dot(hd,normal);

		if(sf >0)
		{
			ds = vec4(light.ls,1.0)*sf*vec4(Mat.ks,1.0);
		}
	}
	res.la = (light.la*Mat.ka)*light.intensity;
	res.ld = vec3(dc)*light.intensity;
	res.ls = vec3(ds)*light.intensity;
	return res;
}

bool InRange(float val,float minVal, float maxVal){
	if(val>=minVal && val<=maxVal)
		return true;
	return false;
}
float sampleRSM(sampler2D Dmap,vec2 coor,float compare){
	return step(compare, texture2D(Dmap, coor).r);
}
float calcShadow(sampler2D Dmap, vec4 coor){
	
	vec4 sh = vec4((coor.xyz/coor.w),1);
	sh.z-=0.05;
	if(InRange(sh.z,0,1) && InRange(sh.x,0,1) && InRange(sh.y,0,1)){
		return sampleRSM(Dmap,sh.xy,sh.z);
	}else{
		return 1.0;
	}
}

vec4 shadowDebug(sampler2D Dmap,vec4 coor){
	//vec4 sh = vec4((coor.xyz/coor.w),1);
	//float val = SampleVSM(Dmap,sh);
	return vec4(0);
	//return texture2D(Dmap,coor.xy);
}
varying vec3 Position;
varying vec3 Normal;
varying vec2 ftexCoord;
varying vec3 Color;
varying mat4 mf;
varying mat3 tbnMatrix;


vuniform mat4 View;
vuniform mat4 Projection;
vuniform mat4 Model;



funiform sampler2D Tex;
funiform bool ApplyNormal;
funiform bool receiveShadow;
funiform vec3 fogColor;
funiform sampler2D NormalTex;
funiform vec3 Epos;
funiform float fogStart;
funiform float fogEnd;
funiform bool fogEnabled;


funiform lightInfo Lights[10];
funiform DirLight dirLight0;
funiform DirLight dirLight1;
funiform DirLight dirLight2;
funiform sampler2D shadowMap0;
funiform sampler2D shadowMap1;
funiform sampler2D shadowMap2;
funiform int LIGHTNUM;
funiform int LIGHTDIRNUM;
funiform materialInfo Mat;

fragment float ComputeFogFactor(float d,float fs,float fe)
{
	if(fogEnabled)
		return clamp((d - fs) / (fe - fs), 0, 1);
	else
		return 0;
}

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

	vec3 n = normalize((Model * vec4(normal, 0.0)).xyz);
    vec3 t = normalize((Model * vec4(tangent, 0.0)).xyz);
    t = normalize(t - dot(t, n) * n);
    
    vec3 biTangent = cross(t, n);
    tbnMatrix = mat3(t, biTangent, n);

	gl_Position = Projection*View*Model*vec4(position,1.0);
}

void FSmain()
{
	vec3 MEINNORMAL = Normal;
	if(ApplyNormal)
		MEINNORMAL = normalize(tbnMatrix * (255.0/128.0 * texture2D(NormalTex, ftexCoord).xyz - 1));

	float fogFactor = ComputeFogFactor(distance(Epos,Position),fogStart,fogEnd);
	//Adding the lights

	//check if there's a texture
	vec4 texC = texture(Tex,ftexCoord);

	lightOut totalDir;
	totalDir.la= vec3(0,0,0);
	totalDir.ld= vec3(0,0,0);
	totalDir.ls= vec3(0,0,0);

	lightOut outd0;
	lightOut outd1;
	lightOut outd2;
	float c0,c1,c2;

	outd0.la = vec3(0);
	outd0.ld = vec3(0);
	outd0.ls = vec3(0);

	outd1.la = vec3(0);
	outd1.ld = vec3(0);
	outd1.ls = vec3(0);

	outd2.la = vec3(0);
	outd2.ld = vec3(0);
	outd2.ls = vec3(0);

	c0=1; c1 =1; c2=1;

	if(LIGHTDIRNUM>=1){
		outd0 = CalcDirLight(dirLight0,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);
		c0 = calcShadow(shadowMap0,dirLight0.shadowMatrix*vec4(Position,1));
		if(receiveShadow){
			outd0.ld *= c0;
		}
	}
	if(LIGHTDIRNUM>=2){
		outd1 = CalcDirLight(dirLight1,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);
		c1 = calcShadow(shadowMap1,dirLight1.shadowMatrix*vec4(Position,1));
		if(receiveShadow)
			outd1.ld *= c1;
	}
	if(LIGHTDIRNUM>=3){
		outd2 = CalcDirLight(dirLight2,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);
		c2 = calcShadow(shadowMap2,dirLight2.shadowMatrix*vec4(Position,1));
		if(receiveShadow)
			outd2.ld *= c2;
	}

	totalDir.la += outd0.la;
	totalDir.ld += outd0.ld;
	totalDir.ls += outd0.ls;

	totalDir.la += outd1.la;
	totalDir.ld += outd1.ld;
	totalDir.ls += outd1.ls;

	totalDir.la += outd2.la;
	totalDir.ld += outd2.ld;
	totalDir.ls += outd2.ls;
	
	
	//Calc the lights
	lightOut AP;
	AP.la=vec3(0,0,0);
	AP.ld=vec3(0,0,0);
	AP.ls=vec3(0,0,0);
	bool fp=true;
	for(int i=0;i<LIGHTNUM;i++){
		lightOut ith = calcLight(Lights[i],Position,normalize(MEINNORMAL),Mat);
		
		if(LIGHTNUM<=1){
			AP.la = ith.la;
			AP.ld = ith.ld;
			AP.ls = ith.ls;
		}else if(fp){
			i++;
			lightOut ith2 = calcLight(Lights[i],Position,normalize(MEINNORMAL),Mat);
			AP.la = ith.la+ith2.la;
			AP.ld = ith.ld+ith2.ld;
			AP.ls = ith.ls+ith2.ls;
			fp = false;
		}else{
			AP.la += ith.la;
			AP.ld += ith.ld;
			AP.ls += ith.ls;
		}
		
	}

	lightOut totalLight;
	totalLight.la = (AP.la+totalDir.la)*Mat.ka;
	totalLight.ld = ((AP.ld+totalDir.ld)+(Color+ vec3(texC) ))*Mat.kd;
	totalLight.ls = (AP.ls+totalDir.ls)*Mat.ks;

	/*
	if(c0<1)
		totalLight.ld *= (dirLight0.intensity)/max(((dirLight0.intensity*dirLight0.intensity)-dirLight0.intensity),1);
	if(c1<1)
		totalLight.ld *= (dirLight1.intensity)/max(((dirLight1.intensity*dirLight1.intensity)-dirLight1.intensity),1);
	if(c2<1)
		totalLight.ld *= (dirLight2.intensity)/max(((dirLight2.intensity*dirLight2.intensity)-dirLight2.intensity),1);
	*/
		
		
	vec4 finale = vec4((totalLight.la+totalLight.ld+totalLight.ls) , 1.0);
	gl_FragColor = vec4(mix((totalLight.la+totalLight.ld+totalLight.ls),fogColor,fogFactor),1);
	//gl_FragColor = shadowDebug(shadowMap0,dirLight0.shadowMatrix*vec4(Position,1));

}
