#version 330
attribute vec3 position;

vuniform mat4 screenToCamera;
vuniform mat4 cameraToWorld;
vuniform mat4 worldToScreen;
vuniform mat2 worldToWind;
vuniform mat2 windToWorld;
vuniform vec3 worldCamera;
vuniform vec3 worldSunDir;

vuniform float nbWaves;
vuniform sampler1D wavesSampler;
vuniform float heightOffset;
vuniform vec2 sigmaSqTotal;
vuniform float time;

vuniform vec4 lods;

vuniform float nyquistMin;
vuniform float nyquistMax;

funiform vec3 seaColor;

varying float lod;
varying vec2 u;
varying vec3 P;
varying vec3 _dPdu;
varying vec3 _dPdv;
varying vec2 _sigmaSq;

void VSmain(){
	gl_Position = position;

	vec3 cameraDir = normalize((screenToCamera * posiiton).xyz);
	vec3 worldDir = (cameraToWorld * vec4(cameraDir,0.0)).xyz;
	float t = (heightOffset - worldCamera.z)/worldDir.z;

	u = worldToWind *(worldCamera.xy + t * worldDir.xy);
	vec3 dPdu = vec3(1.0,0,0);
	vec3 dPdv = vec3(0,1.0,0);
	vec2 sigmaSq = sigmaSqTotal;

	lod = -t/worldDir.z * lods.y;

	vec3 dP = vec3(0,0,heightOffset);
	float iMin = max(0,floor((log2(nyquistMin * lod)-lods.z)*lods.w));

	for (float i = iMin; i < nbWaves; i += 1.0) {
        vec4 wt = texture1DLod(wavesSampler, (i + 0.5) / nbWaves, 0.0);
        float phase = wt.y * time - dot(wt.zw, u);
        float s = sin(phase);
        float c = cos(phase);
        float overk = g / (wt.y * wt.y);

        float wp = smoothstep(nyquistMin, nyquistMax, (2.0 * M_PI) * overk / lod);

        vec3 factor = wp * wt.x * vec3(wt.zw * overk, 1.0);
        dP += factor * vec3(s, s, c);

        vec3 dPd = factor * vec3(c, c, -s);
        dPdu -= dPd * wt.z;
        dPdv -= dPd * wt.w;

        wt.zw *= overk;
        float kh = wt.x / overk;
        sigmaSq -= vec2(wt.z * wt.z, wt.w * wt.w) * (1.0 - sqrt(1.0 - kh * kh));
    }

    P = vec3(windToWorld * (u + dP.xy), dP.z);

    if (t > 0.0) {
        gl_Position = worldToScreen * vec4(P, 1.0);
    }

    _dPdu = dPdu;
    _dPdv = dPdv;
    _sigmaSq = sigmaSq;
}

