#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include"Texture.h"
#include"Shader.h"
#include<vector>
using namespace std;

class FrameBuffer{
public:
	FrameBuffer();
	FrameBuffer(vector<Texture*> t);
	~FrameBuffer();

	void clear();
	void init();
	void bind();
	void unbind();
	void resize(unsigned int width, unsigned int height);
	void resizeViewport();

	void bindTransmitTextures(Shader* shader);
	Texture* getTexture(unsigned int ix);

	unsigned int getWidth();
	unsigned int getHeight();
protected:
	unsigned int Uid, Width, Height;
	unsigned int DepthBuffer, size, *drawBuffers;
	vector<Texture*> textures;

};
#endif