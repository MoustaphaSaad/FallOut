#include"Geometry.h"
#include<GL\glew.h>
#include<memory>

Geometry::Geometry(IVertex* vertices,int* indices,int nbVertices,int nbIndices,VertexFormat* form){
	verticesTab = vertices;
	indicesTab = indices;
	format = form;


    this->verticesCount = nbVertices;
    this->indicesCount = nbIndices;

    hNormals = false;
    hTexCoords = false;

	primitive = GL_TRIANGLES;

	//calcNormals();

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

void Geometry::calcNormals(){
	Vertex* vertices = (Vertex*)verticesTab;
		for(int i=0;i<indicesCount;i+=3){
			int i0=indicesTab[i];
			int i1=indicesTab[i+1];
			int i2=indicesTab[i+2];

			vec3 v1 = vertices[i1].position - vertices[i0].position;
			vec3 v2 = vertices[i2].position - vertices[i0].position;

			vec3 normal = v1.Cross(v2).Normalized();

			vertices[i0].normal += normal;
			vertices[i1].normal += normal;
			vertices[i2].normal += normal;

		}
		for(int i = 0; i < verticesCount; i++)
			vertices[i].normal= vertices[i].normal.Normalized();

}