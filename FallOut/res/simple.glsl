#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;

vuniform mat4 MVP;

void VSmain(){
	gl_Position = MVP*vec4(position,1.0);
}

void FSmain(){
	gl_FragColor = vec4(1.0);
}