#include"ObjLoader.h"
#include<iostream>
#include<sstream>
#include<vector>
#include"Math3D.h"
#include"Material.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>


Mesh* ObjLoader::loadObj(const string resourceName,string fileName){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName.c_str(),aiProcess_Triangulate|aiProcess_GenSmoothNormals);
	if(scene){
		vector<Vertex> vertices;
		vector<int> indices;

		const aiMesh* Lmesh = scene->mMeshes[0];
		const aiVector3D Zero3D(0.0f,0.0f,0.0f);
		const aiColor4D EmptyColor(0.0f,0.0f,0.0f,0.0f);

		for(unsigned int i=0;i<Lmesh->mNumVertices;i++){
			const aiVector3D* pPos = &(Lmesh->mVertices[i]);
			const aiVector3D* pNormal =Lmesh->HasNormals()? &(Lmesh->mNormals[i]):&Zero3D;
			const aiColor4D* pColor =Lmesh->HasVertexColors(0)? (Lmesh->mColors[i]):&EmptyColor;
			const aiVector3D* pTexCoord = Lmesh->HasTextureCoords(0) ? &(Lmesh->mTextureCoords[0][i]) : &Zero3D;

			vec3 pos = vec3(pPos->x,pPos->y,pPos->z);
			vec3 norm = vec3(pNormal->x,pNormal->y,pNormal->z);
			vec3 col = vec3(pColor->r,pColor->g,pColor->b);
			vec2 tex = vec2(pTexCoord->x,pTexCoord->y);

			vertices.push_back(Vertex(pos,norm,col,tex));
		}

		for(unsigned int i=0;i<Lmesh->mNumFaces;i++){
			const aiFace& face = Lmesh->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		Geometry* geo = new Geometry(&vertices[0],&indices[0],vertices.size(),indices.size(),new VertexDescription());
		Mesh* mesh = new Mesh(resourceName,geo,new Material("moka"));
		return mesh;
	}else{
		printf("Can't read file %s\n",fileName.c_str());
		return NULL;
	}
}
