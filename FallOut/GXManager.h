#ifndef GXManager_H
#define GXManager_H
#include"Math3D.h"
#include"Display.h"
#include"GlobalStructs.h"
#include<vector>
#include<GL\glew.h>
using namespace std;
class GXManager{
public:
	GXManager(){
		clearColor = vec3();
	}
	virtual void initiate(Display d){}
	virtual void start(){}

	unsigned int CreateTexture(int width, int height, unsigned char* data, bool linearFiltering, bool repeatTexture){ return -1;}
	void DeleteTexture(unsigned int texture){}
	void BindTexture(unsigned int texture, int unit){}
	static void clearBuffers(){}

	virtual unsigned int CreateVertexShader(const string txt){return 0;}
	virtual unsigned int CreateFragmentShader(const string txt){return 0;}
	virtual unsigned int CreateShader(const string txt,unsigned int){return 0;}
	virtual unsigned int CreateProgram(unsigned int* shdrs,int size){return 0;}
	virtual vector<UniformData> CreateUniforms(const string shdr,unsigned int program){return vector<UniformData>();}
	virtual void DeleteShader(unsigned int program,unsigned int* shaders,int size){}
	virtual void BindShader(unsigned int p){}

	virtual void setUniform(unsigned int loc,int value){}
	virtual void setUniform(unsigned int loc,float value){}
	virtual void setUniform(unsigned int loc,const vec3 value){}
	virtual void setUniform(unsigned int loc,const mat4 value){}

	vec3 getClearColor(){
		return clearColor;
	}
	void setClearColor(vec3 val){
		clearColor = val;
	}
protected:
	vec3 clearColor;
};
#endif