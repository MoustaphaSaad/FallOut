#include"Mesh.h"
#include<GL\glew.h>
#include"Engine.h"
Mesh::Mesh(const string name,Geometry* geo,Material* mat):Resource(name,ResourceType::MESH){
	this->geometry = geo;
	this->material = mat;

	vbo = Engine::getEngine()->getGXManager()->CreateVertexBuffer(geo->getVertices(),geo->getVerticesCount()*geo->getFormat()->vertexSize,true);
	ibo = Engine::getEngine()->getGXManager()->CreateIndexBuffer(geo->getIndices(),geo->getIndicesCount()*sizeof(int),true);
}
Mesh::Mesh(Geometry* geo,Material* mat):Resource(){
	this->type = ResourceType::MESH;
	this->geometry = geo;
	this->material = mat;

	vbo = Engine::getEngine()->getGXManager()->CreateVertexBuffer(geo->getVertices(),geo->getVerticesCount()*geo->getFormat()->vertexSize,true);
	ibo = Engine::getEngine()->getGXManager()->CreateIndexBuffer(geo->getIndices(),geo->getIndicesCount()*sizeof(int),true);

}

Mesh::~Mesh(){
	delete this->geometry;
	delete this->material;
}

Geometry* Mesh::getGeometry(){
	return this->geometry;
}
Material* Mesh::getMaterial(){
	return material;
}

void Mesh::setGeometry(Geometry val){
	this->geometry = &val;
}
void Mesh::setMaterial(Material* val){
	this->material = val;
}

void Mesh::draw(){
	Engine::getEngine()->getRenderer()->drawMesh(this);
}
