#include"Mesh.h"
#include<GL\glew.h>
#include"Engine.h"
Mesh::Mesh(const string name,Geometry* geo,Material* mat):Resource(name,ResourceType::MESH){
	this->geometry = geo;
	this->material = mat;
	subMesh = vector<Mesh*>();
	vbo = Engine::getEngine()->getGXManager()->CreateVertexBuffer(geo->getVertices(),geo->getVerticesCount()*geo->getFormat()->vertexSize,true);
	ibo = Engine::getEngine()->getGXManager()->CreateIndexBuffer(geo->getIndices(),geo->getIndicesCount()*sizeof(int),true);
}
Mesh::Mesh(Geometry* geo,Material* mat):Resource(){
	this->type = ResourceType::MESH;
	this->geometry = geo;
	this->material = mat;
	subMesh = vector<Mesh*>();
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

void Mesh::updateGeometry(Geometry* val){
	Engine::getEngine()->getGXManager()->MapBuffer(val->getVertices(), val->getVerticesCount()*val->getFormat()->vertexSize, vbo);
}

void Mesh::draw(){
	Engine::getEngine()->getRenderer()->drawMesh(this);
}

void Mesh::addSubMesh(Mesh* val){
	subMesh.push_back(val);
}
Mesh* Mesh::getSubMesh(int i){
	return subMesh[i];
}
int Mesh::getSubMeshCount(){
	return subMesh.size();
}
