#ifndef DEPTH_TEXTURE
#define DEPTH_TEXTURE
#include"Texture.h"
#include"Engine.h"
class DepthTexture :public Texture{
public:
	DepthTexture(){
		this->type = ResourceType::TEXTURE;
		width = Engine::getInstance()->getDisplay()->width;
		height = Engine::getInstance()->getDisplay()->height;
		TextureID = Engine::getInstance()->getGXManager()->CreateDepthTexture(width, height, NULL);
	}
	DepthTexture(int x,int y){
		this->type = ResourceType::TEXTURE;
		width = x;
		height = y;
		TextureID = Engine::getInstance()->getGXManager()->CreateDepthTexture(width, height, NULL);
	}

};
#endif