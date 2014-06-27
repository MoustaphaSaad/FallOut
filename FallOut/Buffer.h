#ifndef BUFFER_H
#define BUFFER_H
#include<memory>
using namespace std;
namespace Fallout{
	class Buffer;
	typedef tr1::shared_ptr<Buffer> BufferPtr;
class Buffer{
protected:
	unsigned int ID, width, height;
public:
	enum Type{
	FRAMEBUFFER, RENDERBUFFER, DEPTHBUFFER
	};
	Buffer(Type t, unsigned int x, unsigned int y);
	Buffer(Type t);
	~Buffer();
	static void unbind(Type t);
	virtual void bind();
	unsigned int getID();
	unsigned int getWidth();
	unsigned int getHeight();
	Type getType();
protected:
	Type type;
};
}
#endif
