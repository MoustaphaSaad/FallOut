#version 400

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;


varying vec3 Position;
varying vec3 Normal;
varying mat4 fMV;
varying vec2 ftexCoord;

vuniform mat4 MVP;
vuniform mat4 MV;

funiform vec3 lightPosition;
funiform vec3 ambient;
funiform vec3 diffuse;
funiform vec3 spec;
funiform vec3 specular;
funiform float shininess;
funiform sampler2D Tex;


vec4 ads()
{
	vec3 lightMV = vec3(vec4(lightPosition,1.0)*fMV);
	vec3 s = normalize(vec3(lightMV-Position));
	vec3 v = normalize(-Position.xyz);
	vec3 r = reflect(-s,Normal);
	vec3 spec = vec3(0.0);
	spec = specular * .75 * pow(max(dot(r,v),0.0),shininess);
	vec3 res = diffuse * .9* max(dot(s,Normal),0.0);
	res += spec;
	return res;
}


void VSmain()
{
	fMV = MV;
	Normal = vec3(normalize(vec4(normal,0)));
	Position = vec3(vec4(position,0)*MV);
	ftexCoord = texCoord;
	gl_Position = MVP*vec4(position,1.0);
}

void FSmain()
{
	vec4 tl = ads();
	tl+=vec4(ambient,1.0);
	vec4 texC = texture(Tex,ftexCoord);
	if(texC.x > 0 && texC.y >0 && texC.z >0 && texC.w > 0)
	//if(texC != zero)
		tl *= texC;
	if(gl_FrontFacing){
		gl_FragColor = tl;
	}else{
		gl_FragColor = tl;
	}


}
