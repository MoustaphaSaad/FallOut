#include"Texture.h"
#include"Engine.h"
#include<iostream>
using namespace std;
Texture::Texture(const std::string fileName, bool linearFiltering, bool repeatTexture) :Resource()
{
	this->type = ResourceType::TEXTURE;
	int x, y, numComponents;
	unsigned char* data = stbi_load(fileName.c_str(), &x, &y, &numComponents, 4);

	if (data == NULL)
		cerr << "Can't Load Texture " << fileName << endl;

	TextureID = Engine::getInstance()->getGXManager()->CreateTexture(x, y, data, linearFiltering, repeatTexture);
	stbi_image_free(data);
	width = x;
	height = y;
}

Texture::Texture(int width, int height, void* data, bool linearFiltering, bool repeatTexture) :Resource()
{
	this->type = ResourceType::TEXTURE;
	TextureID = Engine::getInstance()->getGXManager()->CreateTexture(width, height, data, linearFiltering, repeatTexture);
	this->width = width;
	this->height = height;
}

Texture::~Texture()
{
	Engine::getInstance()->getGXManager()->DeleteTexture(TextureID);
}

void Texture::bind(int unit) const
{
	Engine::getInstance()->getGXManager()->BindTexture(TextureID, unit);
}
void Texture::unbind(int unit){
	Engine::getInstance()->getGXManager()->BindTexture(0, unit);
}
