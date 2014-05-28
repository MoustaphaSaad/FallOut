#include "FrameBuffer.h"
#include"DepthTexture.h"
#include"Engine.h"
FrameBuffer::FrameBuffer() :Buffer(BufferType::FRAMEBUFFER){
	addBuffer(new Buffer(BufferType::RENDERBUFFER));
	addBuffer(new Buffer(BufferType::DEPTHBUFFER));
	addDepthTexture(new DepthTexture());
	addTexture(new Texture(Engine::getInstance()->getDisplay()->width, Engine::getInstance()->getDisplay()->height));
}
FrameBuffer::FrameBuffer(int w,int h):Buffer(BufferType::FRAMEBUFFER){
	addBuffer(new Buffer(BufferType::RENDERBUFFER,w,h));
	addBuffer(new Buffer(BufferType::DEPTHBUFFER,w,h));
	addDepthTexture(new DepthTexture(w,h));
	addTexture(new Texture(w, h));
}
void FrameBuffer::addBuffer(Buffer* b){
	if (b->getType() == BufferType::DEPTHBUFFER)
		DepthBuffer = b;
	else if (b->getType() == BufferType::RENDERBUFFER)
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
	RenderBuffer->bind();
	DepthBuffer->bind();
}
void FrameBuffer::unbindFB(){
	this->unbind(BufferType::FRAMEBUFFER);
	RenderBuffer->unbind(RenderBuffer->getType());
	DepthBuffer->unbind(DepthBuffer->getType());	
	RenderTexture->unbind();
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