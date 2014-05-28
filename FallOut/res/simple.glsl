#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;

vuniform mat4 Projection;
vuniform mat4 View;
vuniform mat4 Model;
varying vec3 Pos;

void VSmain(){
	Pos = position;
	gl_Position = Projection*View*Model*vec4(position,1.0);
}

void FSmain(){
	gl_FragColor = vec4(Pos.z*1.0,0,0,1);
}