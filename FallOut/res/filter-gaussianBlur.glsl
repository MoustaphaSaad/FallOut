#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;

vuniform mat4 Projection;
vuniform mat4 View;
vuniform mat4 Model;

funiform vec3 blurScale;
funiform sampler2D Tex;

varying vec2 texCoord0;



void VSmain(){
	texCoord0 = texCoord;
	gl_Position = Projection*View*Model*vec4(position,1.0);
}

void FSmain(){
	
	vec4 color = vec4(0.0);
	
	color += texture2D(Tex, texCoord0 + (vec2(-3.0) * blurScale.xy)) * (1.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(-2.0) * blurScale.xy)) * (6.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(-1.0) * blurScale.xy)) * (15.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(0.0) * blurScale.xy))  * (20.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(1.0) * blurScale.xy))  * (15.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(2.0) * blurScale.xy))  * (6.0/64.0);
	color += texture2D(Tex, texCoord0 + (vec2(3.0) * blurScale.xy))  * (1.0/64.0);
	gl_FragColor = color;
}