#ifndef BUFFER_H
#define BUFFER_H
enum BufferType{
	FRAMEBUFFER, RENDERBUFFER, DEPTHBUFFER
};
class Buffer{
protected:
	unsigned int ID, width, height;
	BufferType type;
public:
	Buffer(BufferType t, unsigned int x, unsigned int y);
	Buffer(BufferType t);
	~Buffer();
	static void unbind(BufferType t);
	virtual void bind();
	unsigned int getID();
	unsigned int getWidth();
	unsigned int getHeight();
	BufferType getType();
};
#endif
