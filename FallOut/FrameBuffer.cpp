#include "FrameBuffer.h"
#include "Core.h"
#include<gl\glew.h>

FrameBuffer::FrameBuffer(){
	Uid = 0;
	textures = vector<Texture*>();
	Width = 1024;
	Height = 1024;
}

FrameBuffer::FrameBuffer(vector<Texture*> t){
	Uid = 0;
	textures = t;
	Width = 1024;
	Height = 1024;
}

FrameBuffer::~FrameBuffer(){
	for each(Texture* tx in textures)
		delete tx;
	textures.clear();
	delete drawBuffers;
}

void FrameBuffer::clear(){
	Fallout::getGXManager()->clearBuffers();
}

void FrameBuffer::init(){
	glGenFramebuffers(1, &Uid);
	glBindFramebuffer(GL_FRAMEBUFFER, Uid);


}
