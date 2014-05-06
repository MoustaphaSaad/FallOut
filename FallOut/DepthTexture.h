#ifndef DEPTH_TEXTURE
#define DEPTH_TEXTURE
#include"Texture.h"
#include"Core.h"
class DepthTexture :public Texture{
public:
	DepthTexture(){
		this->type = ResourceType::TEXTURE;
		width = 1024;
		height = 1024;
		TextureID = Fallout::getGXManager()->CreateDepthTexture(width, height, 0);
		
	}
	DepthTexture(int x,int y){
		this->type = ResourceType::TEXTURE;
		width = x;
		height = y;
		TextureID = Fallout::getGXManager()->CreateDepthTexture(width, height, 0);

	}

};
#endif