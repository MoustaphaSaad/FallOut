#include"Texture.h"
#include"Engine.h"
#include<iostream>
using namespace std;
Texture::Texture(const string ResourceName,const std::string fileName, bool linearFiltering, bool repeatTexture):Resource(ResourceName,ResourceType::TEXTURE)
{
	this->type = ResourceType::TEXTURE;
    int x, y, numComponents;
    unsigned char* data = stbi_load(fileName.c_str(), &x, &y, &numComponents, 4);

    if(data == NULL)
		cerr<<"Can't Load Texture "<<fileName<<endl;

	TextureID = Engine::getEngine()->getGXManager()->CreateTexture(x, y, data, linearFiltering, repeatTexture);
    stbi_image_free(data);
	
}

Texture::Texture(const string ResourceName,int width, int height, unsigned char* data, bool linearFiltering, bool repeatTexture):Resource(ResourceName,ResourceType::TEXTURE)
{
	this->type = ResourceType::TEXTURE;
	TextureID = Engine::getEngine()->getGXManager()->CreateTexture(width, height, data, linearFiltering, repeatTexture);
}

Texture::~Texture()
{
	Engine::getEngine()->getGXManager()->DeleteTexture(TextureID);
}

void Texture::bind(int unit) const
{
	Engine::getEngine()->getGXManager()->BindTexture(TextureID, unit);
}
