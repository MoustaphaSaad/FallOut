#ifndef GLSLTRANsLaTOR_H
#define GLSLTRANsLaTOR_H
#include<string>
#include"GlobalStructs.h"
#include<stack>
using namespace std;
namespace Fallout{
class GLSL{
public:
	enum Shaders{VERTEX,FRAGMENT};
	static string removeFunction(const string txt, string funcName);
	static string removeFunctionCategory(const string txt, const string key);
	static string InOutManagement(const string txt, Shaders type);
	static string UniformManagement(const string txt, Shaders type);
	static vector<UniformData> CreateUniforms(const string txt, unsigned int program, vector<ShaderStruct> strct);
	static vector<ShaderStruct> CreateStructs(const string shdr, unsigned int program);
	static string process(string txt,Shaders type);
};
}
#endif