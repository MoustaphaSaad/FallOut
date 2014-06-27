#ifndef VERTEX_H_
#define VERTEX_H_
#include"Math3D.h"
namespace Fallout{
class IVertex{
public:
	IVertex(){}
	~IVertex(){}
};
class Vertex:public IVertex{
public:
	Vertex(vec3 pos = vec3(),vec3 norm = vec3(0,0,0),vec3 co = vec3(-1,-1,-1),vec2 tex = vec2(),vec3 tan = vec3()){
		position = pos;
		normal = norm;
		color = co;
		texCoord = tex;
		tangent = tan;
	}
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texCoord;
	vec3 tangent;

};
class DefVertex2D :public IVertex{
public:
	DefVertex2D(vec2 pos = vec2(), vec3 co = vec3(-1, -1, -1), vec2 tc = vec2()){
		position = pos;
		color = co;
		texCoord = tc;

	}
	vec2 position;
	vec3 color;
	vec2 texCoord;
};
}
#endif