#version 330
attribute vec2 position;
attribute vec3 color;
attribute vec2 texCoord;

varying vec3 Color;

vuniform mat4 screenToCamera;
vuniform mat4 cameraToWorld;
funiform vec3 worldCamera;
funiform vec3 worldSunDir;

varying vec3 viewDir;


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
    viewDir = (inverse(cameraToWorld) * vec4((inverse(screenToCamera) * vec4(position,1,1)).xyz, 1.0)).xyz;
	Color = color;
	gl_Position = vec4(position.xy,0.999,1);
}

void FSmain(){
	vec3 v = normalize(viewDir);
	vec3 sunColor = vec3(step(0.999, dot(v, worldSunDir))) * SUN_INTENSITY;
	vec3 ext;
	vec3 inscatter = skyRadiance(worldCamera + earthPos, v, worldSunDir, ext);
	
	vec3 final = sunColor + ext + inscatter;
	gl_FragColor.rgb = hdr(final);
	gl_FragColor.a = 1.0;
	
}