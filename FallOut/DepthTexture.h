#ifndef DEPTH_TEXTURE
#define DEPTH_TEXTURE
#include"Texture.h"
#include"Engine.h"
namespace Fallout{
class DepthTexture :public Texture{
public:
	DepthTexture(){
		this->type = Resource::Type::TEXTURE;
		width = Engine::getInstance()->getDisplay()->width;
		height = Engine::getInstance()->getDisplay()->height;
		TextureID = Engine::getInstance()->getGXManager()->CreateDepthTexture(width, height, NULL);
	}
	DepthTexture(int x,int y){
		this->type = Resource::Type::TEXTURE;
		width = x;
		height = y;
		TextureID = Engine::getInstance()->getGXManager()->CreateDepthTexture(width, height, NULL);
	}

};
}
#endif