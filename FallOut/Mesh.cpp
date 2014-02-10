#include"Mesh.h"
#include<GL\glew.h>
Mesh::Mesh(const string name,Geometry* geo,Material* mat):Resource(name,ResourceType::MESH){
	this->geometry = geo;
	this->material = mat;

	glGenBuffers(1,&vbo);
	glGenBuffers(1,&ibo);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	int g = geometry->getVerticesCount();
	glBufferData(GL_ARRAY_BUFFER,g*geo->getFormat()->vertexSize,geo->getVertices(),GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndicesCount() * sizeof(int), geometry->getIndices(), GL_STATIC_DRAW);
}

Mesh::~Mesh(){
	delete this->geometry;
	delete this->material;
}

Geometry* Mesh::getGeometry(){
	return this->geometry;
}
Material* Mesh::getMaterial(){
	return this->material;
}

void Mesh::setGeometry(Geometry val){
	this->geometry = &val;
}
void Mesh::setMaterial(Material val){
	this->material = &val;
}

void Mesh::draw(){
	//RendererEngine.Draw(geometry,material);
	


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
