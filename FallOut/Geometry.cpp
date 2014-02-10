#include"Geometry.h"
#include<GL\glew.h>
#include<memory>

Geometry::Geometry(IVertex* vertices,int* indices,int nbVertices,int nbIndices,VertexFormat* form){
	verticesTab = vertices;
	indicesTab = indices;
	format = form;

	//memcpy(verticesTab, vertices, nbVertices * form->vertexSize);
    //memcpy(indicesTab, indices, nbIndices * sizeof(int));


    this->verticesCount = nbVertices;
    this->indicesCount = nbIndices;

    hNormals = false;
    hTexCoords = false;

	primitive = GL_TRIANGLES;

}
IVertex* Geometry::getVertices()
{
    return verticesTab;
}

int* Geometry::getIndices()
{
    return indicesTab;
}

int Geometry::getVerticesCount()
{
    return verticesCount;
}

int Geometry::getIndicesCount()
{
    return indicesCount;
}

bool Geometry::hasNormals()
{
    return hNormals;
}

bool Geometry::hasTexCoords()
{
    return hTexCoords;
}

void Geometry::setPrimitive(unsigned int glenum)
{
    primitive = glenum;
}

unsigned int Geometry::getPrimitive()
{
    return primitive;
}

VertexFormat* Geometry::getFormat(){
	return format;
}
