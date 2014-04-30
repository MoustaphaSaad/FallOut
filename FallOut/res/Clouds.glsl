#version 330
attribute vec3 position;
attribute vec3 color;
attribute vec2 texCoord;


vuniform mat4 worldToScreen;
funiform vec3 worldCamera;
funiform vec3 worldSunDir;

varying vec3 worldP;
varying vec2 tx;

funiform sampler2D transmittanceSampler;
funiform sampler2D skyIrradianceSampler;
funiform sampler3D inscatterSampler;
funiform sampler2D skySampler;
funiform float hdrExposure;

funiform sampler2D noiseSampler;
funiform float octaves;
funiform float lacunarity;
funiform float gain;
funiform float norm;

funiform float clamp1;
funiform float clamp2;

funiform vec4 cloudsColor;
#include <res/Atmosphere.glh>

void VSmain(){
	gl_Position = worldToScreen * vec4(position,1);
	worldP = position;
	tx = texCoord;
}

void FSmain(){

	gl_FragColor = cloudColor(worldP, worldCamera, worldSunDir);
	gl_FragColor = texture(transmittanceSampler,tx);
    gl_FragColor.rgb = hdr(gl_FragColor.rgb);
	//gl_FragColor = vec4(1,0,0,1);
}