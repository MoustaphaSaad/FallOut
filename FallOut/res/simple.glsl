#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;
attribute vec3 tangent;

vuniform mat4 Projection;
vuniform mat4 View;
vuniform mat4 Model;



void VSmain(){
	gl_Position = Projection*View*Model*vec4(position,1.0);
}

void FSmain(){
	float depth = gl_FragCoord.z;
	gl_FragColor = vec4(depth);
}