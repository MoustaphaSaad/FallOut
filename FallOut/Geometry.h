#ifndef GOEMETRY_H_
#define GOEMETRY_H_
#include"GlobalStructs.h"
#include"Vertex.h"
#include<memory>
using namespace std;

namespace Fallout{
	class Geometry;
	typedef tr1::shared_ptr<Geometry> GeometryPtr;
class Geometry{
public:
	Geometry(IVertex* vertices, int* indices, int nbVertices, int nbIndices, VertexFormat* form);
	IVertex* getVertices();
	int* getIndices();

	int getVerticesCount();
	int getIndicesCount();

	VertexFormat* getFormat();


private:
	IVertex* verticesTab;
	int* indicesTab;
	int verticesCount;
	int indicesCount;

	VertexFormat* format;
};

}

#endif