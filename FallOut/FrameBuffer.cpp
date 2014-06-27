#include "FrameBuffer.h"
#include"DepthTexture.h"
#include"Engine.h"
using namespace Fallout;
FrameBuffer::FrameBuffer() :Buffer(Buffer::Type::FRAMEBUFFER,Engine::getInstance()->getDisplay()->width,Engine::getInstance()->getDisplay()->height){
	RenderBuffer=NULL;
	DepthBuffer=NULL;
	//mDepthTexture = NULL;
	//RenderTexture = NULL;
	//addBuffer(new Buffer(Buffer::Type::RENDERBUFFER));
	//addBuffer(new Buffer(Buffer::Type::DEPTHBUFFER));
	addDepthTexture(new DepthTexture());
	addTexture(new Texture(Engine::getInstance()->getDisplay()->width, Engine::getInstance()->getDisplay()->height));
}
FrameBuffer::FrameBuffer(int w,int h):Buffer(Buffer::Type::FRAMEBUFFER,w,h){
	RenderBuffer=NULL;
	DepthBuffer=NULL;
	//mDepthTexture = NULL;
	//RenderTexture = NULL;
	//addBuffer(new Buffer(Buffer::Type::RENDERBUFFER,w,h));
	//addBuffer(new Buffer(Buffer::Type::DEPTHBUFFER,w,h));
	addDepthTexture(new DepthTexture(w,h));
	addTexture(new Texture(w, h));
}
void FrameBuffer::addBuffer(Buffer* b){
	if (b->getType() == Buffer::Type::DEPTHBUFFER)
		DepthBuffer = b;
	else if (b->getType() == Buffer::Type::RENDERBUFFER)
		RenderBuffer = b;

	Engine::getInstance()->getGXManager()->addBuffertoFB(b->getType(), this->ID, b->getID());
}
void FrameBuffer::addDepthTexture(Texture* txt){
	mDepthTexture = txt;
	Engine::getInstance()->getGXManager()->addDepthTexturetoFB(txt, ID);
}
void FrameBuffer::addTexture(Texture* txt){
	RenderTexture = txt;
	Engine::getInstance()->getGXManager()->addTexturetoFB(txt, ID);
}
void FrameBuffer::bind(){
	Buffer::bind();
	if(RenderBuffer!=NULL)
		RenderBuffer->bind();
	if(DepthBuffer!=NULL)
		DepthBuffer->bind();
}
void FrameBuffer::unbindFB(){
	this->unbind(Buffer::Type::FRAMEBUFFER);
	if(RenderBuffer!=NULL)
		RenderBuffer->unbind(RenderBuffer->getType());
	if(DepthBuffer!=NULL)
		DepthBuffer->unbind(DepthBuffer->getType());
	if(RenderTexture!=NULL)
		RenderTexture->unbind();
	if(mDepthTexture!=NULL)
		mDepthTexture->unbind();
}

Texture* FrameBuffer::getDepth(){
	return mDepthTexture;
}
Texture* FrameBuffer::getRenderTexture(){
	return RenderTexture;
}
Buffer* FrameBuffer::getRenderBuffer(){
	return RenderBuffer;
}
Buffer* FrameBuffer::getDepthBuffer(){
	return DepthBuffer;
}