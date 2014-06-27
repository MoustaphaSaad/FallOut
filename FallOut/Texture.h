#ifndef Texture_H
#define Texture_H
#include<string>
#include<memory>

#include"stb_image.h"
#include"Resources.h"
using namespace std;
namespace Fallout{
	class Texture;
	typedef tr1::shared_ptr<Texture> TexturePtr;
class Texture :public Resource{
public:
	Texture(const string fileName, bool linearFiltering = false, bool repeatTexture = true);
	Texture(int width = 0, int height = 0, void* data = 0, bool linearFiltering = false, bool repeatTexture = true);

	void bind(int uint = 0) const; 
	static void unbind(int unit = 0);

	int getWidth();
	int getHeight();
	unsigned int getID(){
		return TextureID;
	}

	~Texture();
	Texture(const Texture& texture) :Resource(texture.name, Resource::Type::TEXTURE){ this->type = Resource::Type::TEXTURE; }
protected:
	void operator=(const Texture& texture){}
	unsigned int TextureID;
	int width, height;
};
}
#endif