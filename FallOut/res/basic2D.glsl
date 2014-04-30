#version 330
attribute vec2 position;
attribute vec3 color;
attribute vec2 texCoord;

varying vec3 Color;

#include <res/Atmosphere.glh>

void VSmain(){
	
	Color = color;
	gl_Position = vec4(position.xy,0.999,1);
}

void FSmain(){
	gl_FragColor = vec4(Color,1);
}