#include"RenderEngine.h"
#include"Shader.h"
#include"Engine.h"
#include"Scene.h"
#include"SimpleShader.h"
#include"Light.h"
#include"ObjLoader.h"
#include"MaterialBasic.h"
using namespace Fallout;
//TODO Clear First;
RenderEngine::RenderEngine(){
	engine = Engine::getInstance();
	shadowShader = new ShadowShader();

}
RenderEngine::~RenderEngine(){
	delete engine;

	delete shadowShader;
}

void RenderEngine::Draw(Transformable* sender, Mesh* mesh,Shader* shdr){

	if (!sender || !mesh)
		return;
	//Drawing Mesh
	if(state == RenderState::Normal){
		mesh->getMaterial()->getShader()->Bind();
		mesh->getMaterial()->use();
		mesh->getMaterial()->getShader()->Update(sender,mesh->getMaterial());
	}else if(state == RenderState::Shadow){

		shadowShader->Bind();
		shadowShader->Update(sender);
		if(!sender->Composer->castShadow)
			return;

	}else if(state == RenderState::Custom){
		/*if(shdr == NULL)
			shdr = mesh->getMaterial()->getShader();
		shdr->Bind();
		mesh->getMaterial()->use();
		shdr->Update(sender);*/
	}
	Engine::getInstance()->getGXManager()->drawGeometry(mesh->getGeometry(), mesh->vbo, mesh->ibo);

	//Drawing Childern
	for (int i = 0; i < mesh->getSubMeshCount(); i++)
		Draw(sender, mesh->getSubMesh(i));

	Shader::unbind();
	Texture::unbind();
}

void RenderEngine::render(Scene* scene){
	state = RenderState::Normal;
	scene->Render();
}
void RenderEngine::shadowPhase(Scene* scene){
	if(scene == NULL)
		return;
	state = RenderState::Shadow;
	for(int i=0;i<scene->DirLights.size();i++){

		scene->DirLights[i]->shadow->ShadowBuffer->bind();
		engine->gxManager->clearBuffers();


		mat4 scaleBias = mat4().InitScale(vec3(0.5,0.5,0.5)) * mat4().InitTranslation(vec3(1,1,1));
		int lim = scene->DirLights[i]->shadow->Radius;
		mat4 ortho = mat4().InitOrthographic(lim,-lim,lim,-lim,lim,-lim);
		scene->DirLights[i]->shadow->shadowMatrix= scaleBias*ortho*scene->DirLights[i]->getPositionRotation(scene->getCamera());
		shadowShader->Light = scene->DirLights[i];
		scene->Render();


		scene->DirLights[i]->shadow->ShadowBuffer->unbindFB();
	}
	Display::BindTarget();

}

void RenderEngine::renderToBuffer(FrameBuffer* buffer,Scene* scene,Shader* shdr){
	if(scene==NULL)
		scene = Engine::getInstance()->getApplication()->getScene();

	if(scene == NULL)
		return;

	buffer->bind();
	Engine::getInstance()->gxManager->clearBuffers();
	if(shdr == NULL)
		state = RenderState::Normal;
	else
		state = RenderState::Custom;

	scene->Render();
	buffer->unbindFB();
	Display::BindTarget();
}