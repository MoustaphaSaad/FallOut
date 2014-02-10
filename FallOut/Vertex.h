#ifndef VERTEX_H_
#define VERTEX_H_
#include"Math3D.h"
class IVertex{
public:
	IVertex(){}
	~IVertex(){}
};
class Vertex:public IVertex{
public:
	Vertex(vec3 pos = vec3(),vec3 norm = vec3(),vec3 co = vec3(),vec2 tex = vec2()){
		position = pos;
		normal = norm;
		color = co;
		texCoord = tex;
	}
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texCoord;

};
#endif