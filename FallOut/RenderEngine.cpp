#include"RenderEngine.h"
#include"Shader.h"
#include"Engine.h"
#include"Scene.h"
#include"SimpleShader.h"
#include"Light.h"

//TODO Clear First;
RenderEngine::RenderEngine(){
	engine = Engine::getInstance();
	FB = new FrameBuffer();
	shadowShader = new SimpleShader();
}
RenderEngine::~RenderEngine(){
	delete engine;
}

void RenderEngine::Draw(Transformable* sender, Mesh* mesh){

	if (!sender || !mesh)
		return;
	//Drawing Mesh
	if(state == RenderState::Normal){
		mesh->getMaterial()->getShader()->Bind();
		mesh->getMaterial()->use();
		mesh->getMaterial()->getShader()->Update(sender);
	}else if(state == RenderState::Shadow){

		shadowShader->Bind();
		shadowShader->Update(sender);

	}
	Engine::getInstance()->getGXManager()->drawGeometry(mesh->getGeometry(), mesh->vbo, mesh->ibo);

	//Drawing Childern
	for (int i = 0; i < mesh->getSubMeshCount(); i++)
		Draw(sender, mesh->getSubMesh(i));
}

void RenderEngine::render(Scene* scene){
	state = RenderState::Normal;
	scene->Render();
}
void RenderEngine::shadowPhase(Scene* scene){
	FB->bind();
	Engine::getInstance()->gxManager->clearBuffers();

	state = RenderState::Shadow;
	Application* app = Engine::getInstance()->getApplication();
	vec3 tPos = app->getScene()->getCamera()->getTransform()->position;
	vec4 tRot = app->getScene()->getCamera()->getTransform()->rotation;
	if (app->getScene()->dirLight != NULL){
		app->getScene()->getCamera()->getTransform()->position = app->getScene()->dirLight->getPosition();
		app->getScene()->getCamera()->getTransform()->rotation = app->getScene()->getCamera()->getTransform()->getLookAtRot(app->getScene()->dirLight->getDirection(), app->getScene()->dirLight->getTransform()->rotation.GetUp());
	}

	float arr[4][4] = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0.5f, 0.5f, 0.5f, 1.0f
	};

	mat4 scaleBias(arr);	
	int lim=15;
	mat4 ortho = mat4().InitOrthographic(lim,-lim,lim,-lim,0.1,-50);

	//shadowMatrix = scaleBias*app->getScene()->getCamera()->getProjection()*app->getScene()->getCamera()->getPositionRotation();
	shadowMatrix = scaleBias*ortho*app->getScene()->getCamera()->getPositionRotation();

	scene->Render();
	
	app->getScene()->getCamera()->getTransform()->position = tPos;
	app->getScene()->getCamera()->getTransform()->rotation = tRot;
	FB->unbindFB();
}
Texture* RenderEngine::getDepth(){
	return FB->getDepth();
}