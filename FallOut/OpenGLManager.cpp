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
#include"InputGL.h"
#include<GL\freeglut.h>
using namespace std;
OpenGLManager::OpenGLManager(Display* d):GXManager(){
	initiate(d);
}
void OpenGLManager::initiate(Display* d){
	int argc=0;
	glutInit(&argc, NULL);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(d->width,d->height);
	glutCreateWindow(d->title.c_str());
	glutInitContextVersion(4, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
		
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
	Engine::getEngine()->getDisplay()->width = w;
	Engine::getEngine()->getDisplay()->height = h;
}
void OpenGLManager::clearBuffers(){
	vec3 val = Engine::getEngine()->getGXManager()->getClearColor();
	glClearColor(val.GetX(),val.GetY(),val.GetZ(),1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

}
void OpenGLManager::refresh(){
	glutPostRedisplay();
}
void OpenGLManager::Idle(){
	Engine::getEngine()->gameLoop();
}
void OpenGLManager::display(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_RGBA);
	glEnable(GL_DOUBLE);
	clearBuffers();
	Engine::getEngine()->render();
	glutSwapBuffers();
}
unsigned int OpenGLManager::CreateTexture(int width, int height, unsigned char* data, bool linearFiltering, bool repeatTexture)
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
string removeFunction(const string txt,string funcName){
	size_t funcPosition = txt.find(funcName);
	stack<char> stk;
	bool started = false;
	size_t i;
	for(i=funcPosition+funcName.length();i<txt.length();i++){
		if(txt[i] == '{'){
			stk.push('{');
			started = true;
		}else if(txt[i] == '}'){
			stk.pop();
		}
		if(stk.empty() && started)
			break;
	}
	string output = txt;
	output.erase(funcPosition,i-funcPosition+1);
	return output;
}
string prepareVS(const string txt){
	string output = txt;
	int i=0;
	while(true){
		string prev = output;
		string rep = "layout(location =";
		//char *x=new char[30];
		//_itoa(i,x,10);
		//rep.append(x);
		rep+=i+48;
		rep += " ) in";
		output = StringOp::findReplaceFirst(output,"attribute",rep);
		if(!prev.compare(output))
			break;
		i++;
	}
	output = StringOp::findReplaceAll(output,"varying","out");
	output = StringOp::findReplaceAll(output,"VSmain()","main()");
	return output;
}
string prepareFS(const string txt){
	string output = txt;
	while(true){
		string prev = output;
		output = StringOp::deleteLine(output,"attribute");
		if(!prev.compare(output))
			break;
	}
	output = StringOp::findReplaceAll(output,"varying","in");
	output = StringOp::findReplaceAll(output,"FSmain()","main()");
	return output;
}
string InOutManagement(const string txt,unsigned int type){
	string output = txt;
	if(type == GL_VERTEX_SHADER){
		output = StringOp::findReplaceAll(output,"vout","out");
		output = StringOp::findReplaceAll(output,"vin","in");
		output = StringOp::deleteLine(output,"fout");
		output = StringOp::deleteLine(output,"fin");
	}else if(type == GL_FRAGMENT_SHADER){
		output = StringOp::findReplaceAll(output,"fout","out");
		output = StringOp::findReplaceAll(output,"fin","in");
		output = StringOp::deleteLine(output,"vout");
		output = StringOp::deleteLine(output,"vin");
	}
	return output;

}
string UniformManagement(const string txt,unsigned int type){
	string output = txt;
	if(type == GL_VERTEX_SHADER){
		output = StringOp::findReplaceAll(output,"vuniform","uniform");
		while(true){
			string prev = output;
			output = StringOp::deleteLine(output,"funiform");
			if(output == prev)
				break;
		}
	}else if(type == GL_FRAGMENT_SHADER){
		output = StringOp::findReplaceAll(output,"funiform","uniform");
		while(true){
			string prev = output;
			output = StringOp::deleteLine(output,"vuniform");
			if(output == prev)
				break;
		}
	}
	return output;

}
unsigned int OpenGLManager::CreateVertexShader(const string txt){
	string shaderTxt = removeFunction(txt,"void FSmain()");
	shaderTxt = removeFunction(shaderTxt,"vec4 ads()");
	shaderTxt = prepareVS(shaderTxt);
	shaderTxt = InOutManagement(shaderTxt,GL_VERTEX_SHADER);
	shaderTxt = UniformManagement(shaderTxt,GL_VERTEX_SHADER);
	return CreateShader(shaderTxt,GL_VERTEX_SHADER);
}
unsigned int OpenGLManager::CreateFragmentShader(const string txt){
	string shaderTxt = removeFunction(txt,"void VSmain()");
	shaderTxt = prepareFS(shaderTxt);
	shaderTxt = InOutManagement(shaderTxt,GL_FRAGMENT_SHADER);
	shaderTxt = UniformManagement(shaderTxt,GL_FRAGMENT_SHADER);
	return CreateShader(shaderTxt,GL_FRAGMENT_SHADER);
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
vector<UniformData> OpenGLManager::CreateUniforms(const string txt,unsigned int program){
	vector<UniformData> output;
	stringstream ss(txt);
	string line;
	while(getline(ss,line)){
		vector<string> substrs = StringOp::Split(line,' ');
		if(substrs.size()>0)
			if(!substrs[0].compare("vuniform")||!substrs[0].compare("funiform")){
				string name = substrs[2];
				for(unsigned int i=0;i<name.size();i++){
					if(name[i] == ';'||name[i] == ' ')
						name.erase(i,1);
				}
				unsigned int location = glGetUniformLocation(program, name.c_str());
				output.push_back(UniformData(location,substrs[1],name));
			}
	}
	return output;
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