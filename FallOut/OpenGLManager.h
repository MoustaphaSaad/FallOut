#ifndef OpenGLManager_H
#define OpenGLManager_H
#include"GXManager.h"
namespace Fallout{
class OpenGLManager : public GXManager{
public:
	OpenGLManager(Display* d);
	void initiate(Display* d);

	void start();
	void clearBuffers();
	static void display();
	static void Idle();
	static void reshapeFunc(int w, int h);

	unsigned int CreateTexture(int width, int height, void* data, bool linearFiltering, bool repeatTexture);
	unsigned int CreateDepthTexture(int width, int height, void* data);
	void DeleteTexture(unsigned int texture);
	void BindTexture(unsigned int texture, int unit);

	unsigned int CreateVertexShader(const string txt);
	unsigned int CreateFragmentShader(const string txt);
	unsigned int CreateShader(const string txt, unsigned int type);
	unsigned int CreateProgram(unsigned int* shdrs, int size);
	void DeleteShader(unsigned int program, unsigned int* shaders, int size);
	void BindShader(unsigned int program);

	void setUniform(unsigned int loc, int value);
	void setUniform(unsigned int loc, float value);
	void setUniform(unsigned int loc, const vec3 value);
	void setUniform(unsigned int loc, const mat4 value);

	unsigned int CreateVertexBuffer(void* data, int dataSize, bool isStatic);
	unsigned int CreateIndexBuffer(void* data, int dataSize, bool isStatic);
	unsigned int CreateDataBuffer(void* data, int dataSize, bool isStatic, int type);
	unsigned int MapBuffer(void* data, int dataSize, unsigned int buffer);

	unsigned int createBuffer(Buffer::Type type, unsigned int w, unsigned int h);
	void deleteBuffer(Buffer::Type type, unsigned int h);
	void bindBuffer(Buffer::Type type, unsigned int h,int x,int y);
	void addBuffertoFB(Buffer::Type type, unsigned int fb, unsigned int b);
	void addDepthTexturetoFB(Texture*txt,unsigned int h);
	void addTexturetoFB(Texture*txt,unsigned int h);

	void refresh();

	void drawGeometry(Geometry* geo, unsigned int vbo, unsigned int ibo);
};
}
#endif