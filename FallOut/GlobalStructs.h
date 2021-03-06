#ifndef GLOBALSTRUCTS
#define GLOBALSTRUCTS
#include<string>
#include<vector>
#include"Math3D.h"
using namespace std;
namespace Fallout{
struct UniformData
{
    unsigned int Location;
    string Type;
    string Name;
    
    UniformData(unsigned int UniformLocation, const std::string& UniformType, const std::string& UniformName)
    {
        Location = UniformLocation;
        Type = UniformType;
        Name = UniformName;
    }
};
struct ShaderStruct{
	vector<UniformData> Data;
	string name;
	ShaderStruct(string n,vector<UniformData> val){
		name = n;
		Data = val;
	}
	ShaderStruct(){
		name="";
		Data = vector<UniformData>();
	}
};
class VertexFormat{
public:
	int vertexSize;
	int nElements;
	vector<int> Sizes;
};
class VertexDescription: public VertexFormat{
public:
	VertexDescription(){
		nElements = 5;
		
		Sizes = vector<int>();
		Sizes.push_back(sizeof(vec3));
		Sizes.push_back(sizeof(vec3));
		Sizes.push_back(sizeof(vec3));
		Sizes.push_back(sizeof(vec2));
		Sizes.push_back(sizeof(vec3));

		vertexSize = sizeof(vec3)+sizeof(vec3)+sizeof(vec3)+sizeof(vec2)+sizeof(vec3);
	}
};
class DefVertex2DDesc : public VertexFormat{
public:
	DefVertex2DDesc(){
		nElements = 3;
		Sizes = vector<int>();
		Sizes.push_back(sizeof(vec2));
		Sizes.push_back(sizeof(vec3));
		Sizes.push_back(sizeof(vec2));
		vertexSize = sizeof(vec2)+sizeof(vec3)+sizeof(vec2);
	}
};
}
#endif