#include"ObjLoader.h"
#include<iostream>
#include<sstream>
#include<vector>
#include"MaterialBasic.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"StringOp.h"
using namespace Fallout;
Material* matHandle(const aiMaterial* Imat,string fileName){
	BasicMaterial* out = new BasicMaterial();
	aiColor4D ambient;
	if(AI_SUCCESS == aiGetMaterialColor(Imat,AI_MATKEY_COLOR_AMBIENT,&ambient)){
		out->setAmbient(vec3(ambient.r,ambient.g,ambient.b));
	}
	aiColor4D diffuse;
	if(AI_SUCCESS == aiGetMaterialColor(Imat,AI_MATKEY_COLOR_DIFFUSE,&diffuse)){
		out->setDiffuse(vec3(diffuse.r,diffuse.g,diffuse.b));
	}
	aiColor4D specular;
	if(AI_SUCCESS == aiGetMaterialColor(Imat,AI_MATKEY_COLOR_SPECULAR,&specular)){
		out->setSpecular(vec3(specular.r,specular.g,specular.b));
	}
	float specularShininess;
	if(AI_SUCCESS == aiGetMaterialFloat(Imat,AI_MATKEY_SHININESS,&specularShininess)){
		out->setShininess(specularShininess);
	}
	vector<string> absPathList = StringOp::Split(fileName,'/');
	string absPath="";
	for(int i=0;i<absPathList.size()-1;i++){
		absPath+=absPathList[i];
		absPath+="/";
	}
	aiString texPath;
	if(AI_SUCCESS == Imat->GetTexture(aiTextureType_DIFFUSE,0,&texPath)){
		Texture* tex = new Texture(absPath+texPath.data);
		out->setTexture(tex);
	}
	if(AI_SUCCESS == Imat->GetTexture(aiTextureType_HEIGHT,0,&texPath)){
		Texture* tex = new Texture(absPath+texPath.data);
		out->setNormalTexture(tex);
	}
	return (Material*)out;

}
Mesh* ObjLoader::loadObj(string fileName){
	Assimp::Importer importer;
	Mesh* output=NULL;
	const aiScene* scene = importer.ReadFile(fileName.c_str(),aiProcess_Triangulate|aiProcess_GenSmoothNormals|aiProcess_GenUVCoords);
	scene = importer.ApplyPostProcessing(aiProcess_CalcTangentSpace);
	if(scene){
		for(int i=0;i<scene->mNumMeshes;i++){
			vector<Vertex> vertices;
			vector<int> indices;
			const aiMesh* Lmesh = scene->mMeshes[i];
			const aiMaterial* mat = scene->mMaterials[Lmesh->mMaterialIndex];
			float diff;
			Material* MeshMat = matHandle(mat,fileName);
			const aiVector3D Zero3D(0.0f,0.0f,0.0f);
			const aiColor4D EmptyColor(0.0f,0.0f,0.0f,0.0f);

			for(unsigned int i=0;i<Lmesh->mNumVertices;i++){
				const aiVector3D* pPos = &(Lmesh->mVertices[i]);
				const aiVector3D* pNormal =&(Lmesh->mNormals[i]);
				const aiColor4D* pColor =Lmesh->HasVertexColors(0)? (Lmesh->mColors[i]):&EmptyColor;
				const aiVector3D* pTexCoord = Lmesh->HasTextureCoords(0) ? &(Lmesh->mTextureCoords[0][i]) : &Zero3D;
				const aiVector3D* pTangent = Lmesh->HasTangentsAndBitangents() ? &(Lmesh->mTangents[i]) : &Zero3D;

				vec3 pos = vec3(pPos->x,pPos->y,pPos->z);
				vec3 norm = vec3(pNormal->x,pNormal->y,pNormal->z);
				vec3 col = vec3(pColor->r,pColor->g,pColor->b);
				vec2 tex = vec2(pTexCoord->x,pTexCoord->y);
				vec3 tanget = vec3(pTangent->x,pTangent->y,pTangent->z);

			

				vertices.push_back(Vertex(pos,norm,col,tex,tanget));
			}

			for(unsigned int i=0;i<Lmesh->mNumFaces;i++){
				const aiFace& face = Lmesh->mFaces[i];
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}

			Geometry* geo = new Geometry(&vertices[0],&indices[0],vertices.size(),indices.size(),new VertexDescription());
			if(output == NULL){
				Mesh* mesh = new Mesh(geo,MeshMat);
				output = mesh;
			}else{
				Mesh* mesh = new Mesh(geo,MeshMat);
				output->addSubMesh(mesh);
			}
		}
		return output;
	}else{
		printf("Can't read file %s\n",fileName.c_str());
		return NULL;
	}
}
