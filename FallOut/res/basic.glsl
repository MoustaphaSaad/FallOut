#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec3 color;
attribute vec2 texCoord;



void VSmain()
{
	gl_Position = vec4(position*0.5,1.0);
}

void FSmain()
{
	gl_FragColor = vec4(1,1,0,1);

}
