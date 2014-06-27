#include"OpenGLManager.h"
#include"StringOp.h"
#include<iostream>
#include<GL\glew.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include"Engine.h"
#include"Shader.h"
#include"Mesh.h"
#include"ObjectRenderer.h"
#include"GLSLTranslator.h"
#include"InputGL.h"
#include<GL\freeglut.h>
#include"Core.h"
using namespace std;
using namespace Fallout;
OpenGLManager::OpenGLManager(Display* d):GXManager(){
	clearColor = vec3();
	initiate(d);
}
void OpenGLManager::initiate(Display* d){
	int argc=0;
	glutInit(&argc, NULL);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA | GLUT_DOUBLE |GLUT_STENCIL );
	glutInitWindowSize(d->width,d->height);
	glutCreateWindow(d->title.c_str());
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_RGBA);
	glEnable(GL_DOUBLE);
	glEnable(GL_CULL_FACE_MODE);
	glEnable(GL_MULTISAMPLE);
}
void OpenGLManager::start(){
	glClearColor(clearColor.GetX(),clearColor.GetY(),clearColor.GetZ(),1);
	glutDisplayFunc(&OpenGLManager::display);
	glutIdleFunc(&OpenGLManager::Idle);
	glutReshapeFunc(&OpenGLManager::reshapeFunc);
	glutKeyboardFunc(&InputGL::keyboardDownFunc);
	glutKeyboardUpFunc(&InputGL::keyboardUpFunc);
	glutMouseFunc(&InputGL::mouseFunc);
	glutMotionFunc(&InputGL::mouseMotionFunc);
	glutPassiveMotionFunc(&InputGL::mouseMotionFunc);
	glutMainLoop();
}
void OpenGLManager::reshapeFunc(int w,int h){
	Fallout::getEngine()->getDisplay()->width = w;
	Fallout::getEngine()->getDisplay()->height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
}
void OpenGLManager::clearBuffers(){
	vec3 val = Fallout::getEngine()->getGXManager()->getClearColor();
	glClearColor(val.GetX(),val.GetY(),val.GetZ(),1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void OpenGLManager::refresh(){
	glutPostRedisplay();
}
void OpenGLManager::Idle(){
	Fallout::getEngine()->gameLoop();
	//display();
}
void OpenGLManager::display(){
	Fallout::getEngine()->gameLoop();
	glutSwapBuffers();
}
unsigned int OpenGLManager::CreateTexture(int width, int height, void* data, bool linearFiltering, bool repeatTexture)
{
	unsigned int texture = 0;
    
	GLfloat filter;
	GLint wrapMode;
        
	if(linearFiltering)
		filter = GL_LINEAR;
	else
		filter = GL_NEAREST;
            
	if(repeatTexture)
		wrapMode = GL_REPEAT;
	else
		wrapMode = GL_NEAREST;
        
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
        
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
	return texture;
}
unsigned int OpenGLManager::CreateDepthTexture(int width, int height, void* data){
	unsigned int texture = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	  // Remove artifact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,GL_COMPARE_R_TO_TEXTURE_ARB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data);
	

	return texture;
}

void OpenGLManager::DeleteTexture(unsigned int texture)
{
	glDeleteTextures(1, &texture);
	
}
void OpenGLManager::BindTexture(unsigned int texture, int unit)
{
	static unsigned int lastTexture = 0;
	if(lastTexture != texture)
	{
		//NOTE: This may fail if GL_TEXTUREX is not ordered sequentially!
		assert(unit >= 0 && unit <= 31);
    	glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture);
		lastTexture = texture;
	}
}
void CheckShaderError(GLuint shader,GLuint flag,bool isProgram, const string msg){
	GLint success =0;
	GLchar error[1024] = {0};

	if(isProgram)
		glGetProgramiv(shader,flag,&success);
	else
		glGetShaderiv(shader,flag,&success);

	if(success == GL_FALSE){
		if(isProgram)
			glGetProgramInfoLog(shader,sizeof(error),NULL,error);
		else
			glGetShaderInfoLog(shader,sizeof(error),NULL,error);		

		printf((msg+" "+error+"\n").c_str());
	}
}
unsigned int OpenGLManager::CreateVertexShader(const string txt){
	return CreateShader(GLSL::process(txt, GLSL::Shaders::VERTEX), GL_VERTEX_SHADER);
}
unsigned int OpenGLManager::CreateFragmentShader(const string txt){
	return CreateShader(GLSL::process(txt, GLSL::Shaders::FRAGMENT), GL_FRAGMENT_SHADER);
}
unsigned int OpenGLManager::CreateShader(const string txt,unsigned int type){
	GLuint shader = glCreateShader(type);

	char* error = new char[1000];
	if(shader == 0)
		printf("Cannot Create Shader\n");

	const GLchar*p[1];
	p[0] = txt.c_str();
	GLint lengths[1];
	lengths[0] = txt.length();

	glShaderSource(shader,1,p,lengths);
	glCompileShader(shader);

	CheckShaderError(shader,GL_COMPILE_STATUS,false,"Error Compiling");

	return shader;
}
unsigned int OpenGLManager::CreateProgram(unsigned int* shdrs,int size){
	unsigned int program = glCreateProgram();
	for(int i=0;i<size;i++)
		glAttachShader(program,shdrs[i]);

	glLinkProgram(program);
	CheckShaderError(program,GL_LINK_STATUS,true,"Error Linking Shader\n");
	glValidateProgram(program);
	CheckShaderError(program,GL_VALIDATE_STATUS,true,"Invalid Shader Program\n");

	return program;
}
void OpenGLManager::DeleteShader(unsigned int program,unsigned int* shaders,int size){
	for(int i = 0; i < size; i++)
    {
        glDetachShader(program,shaders[i]);
        glDeleteShader(shaders[i]);
    }
    
    glDeleteProgram(program);
}
void OpenGLManager::BindShader(unsigned int program)
{
    static unsigned int lastProgram = 0;
    
    if(lastProgram != program)
    {
        glUseProgram(program);
        lastProgram = program;
    }
}

void OpenGLManager::setUniform(unsigned int loc,int value){
	glUniform1i(loc,value);
}
void OpenGLManager::setUniform(unsigned int loc,float value){
	glUniform1f(loc,value);
}
void OpenGLManager::setUniform(unsigned int loc,const vec3 value){
	glUniform3f(loc,value.GetX(),value.GetY(),value.GetZ());
}
void OpenGLManager::setUniform(unsigned int loc,const mat4 value){
	glUniformMatrix4fv(loc,1,GL_TRUE,&(value[0][0]));
}

unsigned int OpenGLManager::CreateVertexBuffer(void* data,int dataSize,bool isStatic){
	return CreateDataBuffer(data,dataSize,isStatic,GL_ARRAY_BUFFER);
}
unsigned int OpenGLManager::CreateIndexBuffer(void* data,int dataSize,bool isStatic){
	return CreateDataBuffer(data,dataSize,isStatic,GL_ELEMENT_ARRAY_BUFFER);
}
unsigned int OpenGLManager::CreateDataBuffer(void* data,int dataSize,bool isStatic,int type){
	unsigned int loc;
	int state;
	if(isStatic)
		state = GL_STATIC_DRAW;
	else
		state = GL_DYNAMIC_DRAW;

	glGenBuffers(1,&loc);

	glBindBuffer(type,loc);
	glBufferData(type,dataSize,data,state);

	return loc;
}

void OpenGLManager::drawGeometry(Geometry* geometry,unsigned int vbo,unsigned int ibo){
	for(int i = 0; i < geometry->getFormat()->nElements; i++)
        glEnableVertexAttribArray(i);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	int memOffset = 0;
    for(int i = 0; i < geometry->getFormat()->nElements; i++)
    {
		int n = geometry->getFormat()->Sizes[i] / sizeof(float);
        glVertexAttribPointer(i, n, GL_FLOAT, GL_FALSE, geometry->getFormat()->vertexSize, (GLvoid*)memOffset);
		memOffset += geometry->getFormat()->Sizes[i];
    }

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);

	for(int i = 0; i < geometry->getFormat()->nElements; i++)
        glDisableVertexAttribArray(i);
}

unsigned int OpenGLManager::MapBuffer(void* data, int dataSize, unsigned int buffer){
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	void* dataGPU = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	memcpy(dataGPU, data, dataSize);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	return 0;
}

unsigned int OpenGLManager::createBuffer(Buffer::Type type,unsigned int w,unsigned int h){
	unsigned int id;
	if (type == Buffer::Type::RENDERBUFFER){
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8,w,h );
	}
	else if (type == Buffer::Type::DEPTHBUFFER){
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_DEPTH_BUFFER, id);
		glRenderbufferStorage(GL_DEPTH_BUFFER, GL_DEPTH_COMPONENT, w, h);
	}
	else if(type == Buffer::Type::FRAMEBUFFER){
		glGenFramebuffers(1, &id);

	}
	return id;

}
void OpenGLManager::deleteBuffer(Buffer::Type type, unsigned int h){
	if (type == Buffer::Type::DEPTHBUFFER || type == Buffer::Type::RENDERBUFFER)
		glDeleteRenderbuffers(1, &h);
	if (type == Buffer::Type::FRAMEBUFFER)
		glDeleteFramebuffers(1, &h);

}
void OpenGLManager::bindBuffer(Buffer::Type type, unsigned int h,int x,int y){
	if (type == Buffer::Type::DEPTHBUFFER)
		glBindRenderbuffer(GL_DEPTH_BUFFER, h);
	else if (type == Buffer::Type::FRAMEBUFFER)
		glBindFramebuffer(GL_FRAMEBUFFER, h);
	else if (type == Buffer::Type::RENDERBUFFER)
		glBindRenderbuffer(GL_RENDERBUFFER, h);

	glViewport(0,0,x,y);
}

void OpenGLManager::addBuffertoFB(Buffer::Type type, unsigned int fb, unsigned int b){
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	if (type == Buffer::Type::DEPTHBUFFER)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_DEPTH_BUFFER, b);
	else if (type == Buffer::Type::RENDERBUFFER)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, b);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLManager::addDepthTexturetoFB(Texture*txt,unsigned int h){
	glBindFramebuffer(GL_FRAMEBUFFER, h);
	txt->bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, txt->getID(),0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void OpenGLManager::addTexturetoFB(Texture*txt,unsigned int h){
	glBindFramebuffer(GL_FRAMEBUFFER, h);
	txt->bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, txt->getID(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}