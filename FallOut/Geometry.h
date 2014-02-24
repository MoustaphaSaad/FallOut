#ifndef GOEMETRY_H_
#define GOEMETRY_H_
#include"GlobalStructs.h"
#include"Vertex.h"
class Geometry{
public:
	Geometry(IVertex* vertices,int* indices,int nbVertices,int nbIndices,VertexFormat* form);
	IVertex* getVertices();
	int* getIndices();

	int getVerticesCount();
	int getIndicesCount();

	VertexFormat* getFormat();

	void setPrimitive(unsigned int glenum);
	unsigned int getPrimitive();

	bool hasNormals();
	bool hasTexCoords();

private:
	IVertex* verticesTab;
	int* indicesTab;
	int verticesCount;
	int indicesCount;

	void calcNormals();

	unsigned int primitive;
	VertexFormat* format;

	bool hNormals;
	bool hTexCoords;
};
#endif