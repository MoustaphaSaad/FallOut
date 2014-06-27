#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include"Buffer.h"
#include"Texture.h"
#include<vector>
#include<memory>
using namespace std;
namespace Fallout{
	class FrameBuffer;
	typedef tr1::shared_ptr<FrameBuffer> FrameBufferPtr;
class FrameBuffer:public Buffer{
public:
	FrameBuffer();
	FrameBuffer(int w,int h);
	~FrameBuffer(){
		if(RenderBuffer!=NULL)
			delete RenderBuffer;
		if(DepthBuffer!=NULL)
			delete DepthBuffer;
		if(RenderTexture!=NULL)
			delete RenderTexture;
		if(mDepthTexture!=NULL)
			delete mDepthTexture;
	}
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
}
#endif