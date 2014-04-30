#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include"FallOut.h"
#include<algorithm>
#include<math.h>
#define M_PI 3.14159265
class Atmosphere :public GameObject{
public:
	Shader* sh;
	Shader* Clouds;
	GameObject* cloud;
	GLuint waveTex;
	Mesh* Ocean = NULL;
	GameObject*gmo = NULL;
	vec3 sun;
	float cameraHeight = 6.0;

	float cameraTheta = 0.0;
	float sunTheta = -3.14159265 / 2.0-0.05;
	float lambdaMin = 0.02;

	float lambdaMax = 30.0;

	float sigmaXsq = 0.0;

	float sigmaYsq = 0.0;

	float meanHeight = 0.0;
	float heightVariance = 0.0;

	float amplitudeMax = 0.0;
	int nbWaves = 60;
	float waveDispersion = 1.25f;

	float heightMax = 0.32;

	float waveDirection = 2.4;

	float U0 = 10.0;

	Quaternion* waves = NULL;
	float sunPhi = 0.0;
	Atmosphere(){
		init();
		cameraTheta = 0;
		gmo = new GameObject();
	}

	void generateMesh(){
			
			float horizon = tan(cameraTheta);
			float s = min(1.1f, 0.5f + horizon * 0.5f);

			float vmargin = 0.1;
			float hmargin = 0.1;

			int height = Fallout::getEngine()->getDisplay()->height;
			int width = Fallout::getEngine()->getDisplay()->width;
			Quaternion vboParams = Quaternion(Fallout::getEngine()->getDisplay()->width, Fallout::getEngine()->getDisplay()->height, 8, cameraTheta);
			vec3 *data = new vec3[int(ceil(Fallout::getEngine()->getDisplay()->height * (s + vmargin) / 8) + 5) * int(ceil(Fallout::getEngine()->getDisplay()->width * (1.0 + 2.0 * hmargin) / 8) + 5)];

			int n = 0;
			int nx = 0;
			for (float j = height * s - 0.1; j > -height * vmargin - 8; j -= 8) {
				nx = 0;
				for (float i = -width * hmargin; i < width * (1.0 + hmargin) + 8; i += 8) {
					data[n++] = vec3(-1.0 + 2.0 * i / width, -1.0 + 2.0 * j / height, 0.0);
					nx++;
				}
			}

			int vboSize = 0;
			int *indices = new int[6 * int(ceil(height * (s + vmargin) / 8) + 4) * int(ceil(width * (1.0 + 2.0 * hmargin) / 8) + 4)];

			int nj = 0;
			for (float j = height * s - 0.1; j > -height * vmargin; j -= 8) {
				int ni = 0;
				for (float i = -width * hmargin; i < width * (1.0 + hmargin); i += 8) {
					indices[vboSize++] = ni + (nj + 1) * nx;
					indices[vboSize++] = (ni + 1) + (nj + 1) * nx;
					indices[vboSize++] = (ni + 1) + nj * nx;
					indices[vboSize++] = (ni + 1) + nj * nx;
					indices[vboSize++] = ni + (nj + 1) * nx;
					indices[vboSize++] = ni + nj * nx;
					ni++;
				}
				nj++;
			}


			if (Ocean == NULL){
				BasicMaterial* mat = new BasicMaterial();
				mat->setShader(new BasicShader());
				vector<Vertex> dave;
				
				for (int i = 0; i < n; i++){
					dave.push_back(Vertex(data[i]));
				}
				Geometry* geo = new Geometry(&dave[0], indices,n, vboSize, new VertexDescription());
				Ocean = new Mesh(geo, mat);
			}
			else{
				vector<Vertex> dave;

				for (int i = 0; i < n; i++){
					dave.push_back(Vertex(data[i]));
				}
				Geometry* geo = new Geometry(&dave[0], indices, n, vboSize, new VertexDescription());
				Ocean->updateGeometry(geo);
			}
	}
	long lrandom(long *seed)
	{
		*seed = (*seed * 1103515245 + 12345) & 0x7FFFFFFF;
		return *seed;
	}

	float frandom(long *seed)
	{
		long r = lrandom(seed) >> (31 - 24);
		return r / (float)(1 << 24);
	}

	inline float grandom(float mean, float stdDeviation, long *seed)
	{
		float x1, x2, w, y1;
		static float y2;
		static int use_last = 0;

		if (use_last) {
			y1 = y2;
			use_last = 0;
		}
		else {
			do {
				x1 = 2.0f * frandom(seed) - 1.0f;
				x2 = 2.0f * frandom(seed) - 1.0f;
				w = x1 * x1 + x2 * x2;
			} while (w >= 1.0f);
			w = sqrt((-2.0f * log(w)) / w);
			y1 = x1 * w;
			y2 = x2 * w;
			use_last = 1;
		}
		return mean + y1 * stdDeviation;
	}

#define srnd() (2*frandom(&seed) - 1)

	void generateWaves()
	{
		long seed = 1234567;
		float min = log(lambdaMin) / log(2.0f);
		float max = log(lambdaMax) / log(2.0f);

		sigmaXsq = 0.0;
		sigmaYsq = 0.0;
		meanHeight = 0.0;
		heightVariance = 0.0;
		amplitudeMax = 0.0;

		if (waves != NULL) {
			delete[] waves;
		}
		waves = new Quaternion[nbWaves];

#define nbAngles 5 // even
#define angle(i) (1.5*(((i)%nbAngles)/(float)(nbAngles/2)-1))
#define dangle() (1.5/(float)(nbAngles/2))

		float Wa[nbAngles]; // normalised gaussian samples
		int index[nbAngles]; // to hash angle order
		float s = 0;
		for (int i = 0; i < nbAngles; i++) {
			index[i] = i;
			float a = angle(i);
			s += Wa[i] = exp(-0.5*a*a);
		}
		for (int i = 0; i < nbAngles; i++) {
			Wa[i] /= s;
		}

		for (int i = 0; i < nbWaves; ++i) {
			float x = i / (nbWaves - 1.0f);

			float lambda = pow(2.0f, (1.0f - x) * min + x * max);
			float ktheta = grandom(0.0f, 1.0f, &seed) * waveDispersion;
			float knorm = 2.0f * M_PI / lambda;
			float omega = sqrt(9.81f * knorm);
			float amplitude;

			float step = (max - min) / (nbWaves - 1); // dlambda/di
			float omega0 = 9.81 / U0;
			if ((i % (nbAngles)) == 0) { // scramble angle ordre
				for (int k = 0; k < nbAngles; k++) {   // do N swap in indices
					int n1 = lrandom(&seed) % nbAngles, n2 = lrandom(&seed) % nbAngles, n;
					n = index[n1];
					index[n1] = index[n2];
					index[n2] = n;
				}
			}
			ktheta = waveDispersion * (angle(index[(i) % nbAngles]) + 0.4*srnd()*dangle());
			ktheta *= 1.0 / (1.0 + 40.0*pow(omega0 / omega, 4));
			amplitude = (8.1e-3*9.81*9.81) / pow(omega, 5) * exp(-0.74*pow(omega0 / omega, 4));
			amplitude *= 0.5*sqrt(2 * M_PI*9.81 / lambda)*nbAngles*step;
			amplitude = 3 * heightMax*sqrt(amplitude);

			if (amplitude > 1.0f / knorm) {
				amplitude = 1.0f / knorm;
			}
			else if (amplitude < -1.0f / knorm) {
				amplitude = -1.0f / knorm;
			}

			waves[i].SetX(amplitude);
			waves[i].SetY(omega);
			waves[i].SetZ(knorm * cos(ktheta));
			waves[i].SetW(knorm * sin(ktheta));
			sigmaXsq += pow(cos(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
			sigmaYsq += pow(sin(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
			meanHeight -= knorm * amplitude * amplitude * 0.5f;
			heightVariance += amplitude * amplitude * (2.0f - knorm * knorm * amplitude * amplitude) * 0.25f;
			amplitudeMax += fabs(amplitude);
		}

		float var = 4.0f;
		amplitudeMax = 2.0f * var * sqrt(heightVariance);

		glActiveTexture(GL_TEXTURE0 + 4);
		glBindTexture(GL_TEXTURE_1D, waveTex);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F_ARB, nbWaves, 0, GL_RGBA, GL_FLOAT, waves);
	}

	void init(){
		generateWaves();
		
		DefVertex2D arr[4] = {
			DefVertex2D(vec2(-1, -1)),
			DefVertex2D(vec2(-1, 1)),
			DefVertex2D(vec2(1, 1)),
			DefVertex2D(vec2(1, -1))
		};
		int indices[6] = { 0, 1, 2, 0, 2, 3 };
		Geometry* gm;
		gm = new Geometry(arr, indices, 4, 6, new DefVertex2DDesc());
		Material* mat = new Material();
		
		sh = new Shader("res/Sky.glsl");
		sh->Bind();
		sh->setUniform("skyIrradianceSampler", 0);
		sh->setUniform("inscatterSampler", 1);
		sh->setUniform("transmittanceSampler", 2);
		sh->setUniform("skySampler", 3);

		

		//3D TEXTURE
		GLuint inscatterTex, transmittanceTex, irradianceTex, noiseTex;
		int res = 64;
		int nr = res / 2;
		int nv = res * 2;
		int nb = res / 2;
		int na = 8;
		FILE *f = fopen("res/inscatter.raw", "rb");
		float *data = new float[nr*nv*nb*na * 4];
		fread(data, 1, nr*nv*nb*na * 4 * sizeof(float), f);
		fclose(f);
		glActiveTexture(GL_TEXTURE0 + 1);
		glGenTextures(1, &inscatterTex);
		glBindTexture(GL_TEXTURE_3D, inscatterTex);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA16F_ARB, na*nb, nv, nr, 0, GL_RGBA, GL_FLOAT, data);
		delete[] data;
		//END 3D TEXTURE

		data = new float[16 * 64 * 3];
		f = fopen("res/irradiance.raw", "rb");
		fread(data, 1, 16 * 64 * 3 * sizeof(float), f);
		fclose(f);
		Texture* koko = new Texture( 64, 16, data);
		koko->bind(0);

		data = new float[256 * 64 * 3];
		f = fopen("res/transmittance.raw", "rb");
		fread(data, 1, 256 * 64 * 3 * sizeof(float), f);
		fclose(f);
		Texture* koko2 = new Texture(256, 64, data);
		koko2->bind(2);


		mat->setShader(sh);
		Mesh* memo = new Mesh(gm, mat);
		this->setRenderComponent(new ObjectRenderer(memo));
	}
	
	void Update(){
		
		GameObject::Update();
	}
	void DrawClouds(vec3 sun,mat4 view,float z){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Clouds->Bind();
		Clouds->setUniform("worldToScreen",view);
		//glUniformMatrix4fv(glGetUniformLocation(clouds->program, "worldToScreen"), 1, true, mat.coefficients());
		Clouds->setUniform("worldCamera", vec3(0,0,-z));
		//glUniform3f(glGetUniformLocation(clouds->program, "worldCamera"), 0.0, 0.0, cameraHeight - meanHeight);
		Clouds->setUniform("worldSunDir", sun);
		//glUniform3f(glGetUniformLocation(clouds->program, "worldSunDir"), sun.x, sun.y, sun.z);
		Clouds->setUniform("hdrExposure", 0.3f);
		//glUniform1f(glGetUniformLocation(clouds->program, "hdrExposure"), hdrExposure);
		Clouds->setUniform("octaves", 10);
		//glUniform1f(glGetUniformLocation(clouds->program, "octaves"), octaves);
		Clouds->setUniform("lacunarity", 2.2f);
		//glUniform1f(glGetUniformLocation(clouds->program, "lacunarity"), lacunarity);
		Clouds->setUniform("gain", 0.7f);
		//glUniform1f(glGetUniformLocation(clouds->program, "gain"), gain);
		Clouds->setUniform("norm", 0.5f);
		//glUniform1f(glGetUniformLocation(clouds->program, "norm"), norm);
		Clouds->setUniform("clamp1", -0.15f);
		//glUniform1f(glGetUniformLocation(clouds->program, "clamp1"), clamp1);
		Clouds->setUniform("clamp2", 0.2f);
		//glUniform1f(glGetUniformLocation(clouds->program, "clamp2"), clamp2);
		//Clouds->setUniform("cloudsColor", Quaternion(1,1,1,1));
		//glUniform4f(glGetUniformLocation(clouds->program, "cloudsColor"), cloudColor[0], cloudColor[1], cloudColor[2], cloudColor[3]);
		cloud->Render();
		glDisable(GL_BLEND);
	}
	void Render(){
		generateMesh();
		if (Engine::getInstance()->getInputManager()->getKey('z') == keyState::DOWN) {
			cameraTheta = min(cameraTheta + 5.0f / 180.0f * M_PI, M_PI / 2.0f - 0.001f);
		}
		else if (Engine::getInstance()->getInputManager()->getKey('x') == keyState::DOWN) {
			cameraTheta = cameraTheta - 5.0 / 180.0 * M_PI;
		}
		sh->Bind();
		sun = vec3(sin(sunTheta) * cos(sunPhi), sin(sunTheta) * sin(sunPhi), cos(sunTheta));
		if (Engine::getInstance()->getInputManager()->getKey('o') == keyState::DOWN)
			sunTheta += .001 ;
		if (Engine::getInstance()->getInputManager()->getKey('k') == keyState::DOWN)
			sunTheta -=.001;
		sun = vec3(sin(sunTheta) * cos(sunPhi), sin(sunTheta) * sin(sunPhi), cos(sunTheta));
		float z = Engine::getInstance()->getApplication()->getScene()->getCamera()->getTransform()->position.GetZ();
		float viewd[4][4] = {
			0.0, -1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, -z,
			-1.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		mat4 view = mat4(viewd);
		view = Engine::getInstance()->getApplication()->getScene()->getCamera()->getTransform()->rotation.ToRotationMatrix()*view;

		sh->setUniform("screenToCamera", Engine::getInstance()->getApplication()->getScene()->getCamera()->getProjection().Transpose());
		sh->setUniform("cameraToWorld", view.Transpose());

		
		sh->setUniform("worldCamera",vec3(0,0,z));
		sh->setUniform("worldSunDir", sun);
		sh->setUniform("hdrExposure", 0.3f);

		
		GameObject::Render();
		gmo = new GameObject();
		gmo->setRenderComponent(new ObjectRenderer(Ocean));
		gmo->Render();
	}
};
#endif