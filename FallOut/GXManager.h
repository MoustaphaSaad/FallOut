#ifndef GXManager_H
#define GXManager_H

#include"Display.h"
#include"GlobalStructs.h"
#include"Geometry.h"
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
	virtual void clearBuffers(){}

	virtual unsigned int CreateTexture(int width, int height, void* data, bool linearFiltering, bool repeatTexture){ return -1; }
	virtual void DeleteTexture(unsigned int texture){}
	virtual void BindTexture(unsigned int texture, int unit){}

	virtual unsigned int CreateVertexShader(const string txt){ return 0; }
	virtual unsigned int CreateFragmentShader(const string txt){ return 0; }
	virtual unsigned int CreateShader(const string txt, unsigned int){ return 0; }
	virtual unsigned int CreateProgram(unsigned int* shdrs, int size){ return 0; }
	virtual void DeleteShader(unsigned int program, unsigned int* shaders, int size){}
	virtual void BindShader(unsigned int p){}

	virtual void setUniform(unsigned int loc, int value){}
	virtual void setUniform(unsigned int loc, float value){}
	virtual void setUniform(unsigned int loc, const vec3 value){}
	virtual void setUniform(unsigned int loc, const mat4 value){}

	virtual unsigned int CreateVertexBuffer(void* data, int dataSize, bool isStatic){ return 0; }
	virtual unsigned int CreateIndexBuffer(void* data, int dataSize, bool isStatic){ return 0; }
	virtual unsigned int CreateDataBuffer(void* data, int dataSize, bool isStatic, int type){ return 0; }
	virtual unsigned int MapBuffer(void* data, int dataSize, unsigned int buffer){ return 0; }

	virtual void refresh(){}

	virtual void drawGeometry(Geometry* geo, unsigned int vbo, unsigned int ibo){}
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