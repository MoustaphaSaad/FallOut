#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include"Buffer.h"
#include"Texture.h"
#include<vector>
using namespace std;
class FrameBuffer:public Buffer{
public:
	FrameBuffer();
	FrameBuffer(int w,int h);
	void addBuffer(Buffer* b);
	void addDepthTexture(Texture* txt);
	void addTexture(Texture* txt);
	void bind();
	void unbindFB();

	Texture* getDepth();
	Texture* getRenderTexture();
	Buffer* getRenderBuffer();
	Buffer* getDepthBuffer();
protected:
	Buffer* RenderBuffer, *DepthBuffer;
	Texture* RenderTexture, *mDepthTexture;
};
#endif