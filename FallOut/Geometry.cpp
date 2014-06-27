#include"Geometry.h"
#include<GL\glew.h>
#include<memory>
using namespace Fallout;
Geometry::Geometry(IVertex* vertices,int* indices,int nbVertices,int nbIndices,VertexFormat* form){
	verticesTab = vertices;
	indicesTab = indices;
	format = form;


    this->verticesCount = nbVertices;
    this->indicesCount = nbIndices;

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

VertexFormat* Geometry::getFormat(){
	return format;
}