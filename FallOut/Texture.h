#ifndef Texture_H
#define Texture_H
#include<string>
#include"stb_image.h"
#include"Resources.h"
using namespace std;

class Texture :public Resource{
public:
	Texture(const string fileName, bool linearFiltering = true, bool repeatTexture = true);
	Texture(int width = 0, int height = 0, void* data = 0, bool linearFiltering = true, bool repeatTexture = true);

	void bind(int uint = 0) const;

	int getWidth();
	int getHeight();
	unsigned int getID(){
		return TextureID;
	}

	~Texture();
	Texture(const Texture& texture) :Resource(texture.name, ResourceType::TEXTURE){ this->type = ResourceType::TEXTURE; }
protected:
	void operator=(const Texture& texture){}
	unsigned int TextureID;
	int width, height;
};
#endif