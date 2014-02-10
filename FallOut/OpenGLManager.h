#ifndef OpenGLManager_H
#define OpenGLManager_H
#include"GXManager.h"

class OpenGLManager : public GXManager{
public:
	OpenGLManager(Display d);
	void initiate(Display d);
	
	void start();
	static void clearBuffers();
	static void display();

	unsigned int CreateTexture(int width, int height, unsigned char* data, bool linearFiltering, bool repeatTexture);
	void DeleteTexture(unsigned int texture);
	void BindTexture(unsigned int texture, int unit);

	unsigned int CreateVertexShader(const string txt);
	unsigned int CreateFragmentShader(const string txt);
	unsigned int CreateShader(const string txt,unsigned int type);
	unsigned int CreateProgram(unsigned int* shdrs,int size);
	vector<UniformData> CreateUniforms(const string txt,unsigned int program);
	void DeleteShader(unsigned int program,unsigned int* shaders,int size);
	void BindShader(unsigned int program);
};
#endif