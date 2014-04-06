#ifndef CLOTH_H
#define CLOTH_H
#include"FallOut.h"
#include<vector>
#define DAMPING 0.01
class Particle{
private:
	bool movable;

	float mass;
	vec3 pos, oldPos, Acc, accNorm;

public:
	Particle(vec3 p){
		pos = p;
		oldPos = pos;
		Acc = vec3(0, 0, 0);
		mass = 1;
		movable = true;
		accNorm = vec3(0, 0, 0);
	}
	Particle()
	{
	}

	void addForce(vec3 f){
		Acc += f / mass;
	}

	void timeStep(){
		if (movable){
			vec3 temp = pos;
			pos = pos + (pos - oldPos)*(1.0 - DAMPING) + Acc*Time::getDelta();
			oldPos = temp;
			Acc = vec3(0, 0, 0);
		}
	}
	vec3 getPos(){ return pos; }

	void resetAcc(){ Acc = vec3(0, 0, 0); }

	void offsetPos(const vec3 v){ if (movable) pos + v; }

	void makeUnmovable(){ movable = false; }

	void addToNormal(vec3 n){
		accNorm += n.Normalized();
		
	}
	
	vec3 getNormal(){ return accNorm; }
	void resetNormal(){ accNorm = vec3(0, 0, 0); }
};

class Constraint{
private:
	float rest_distance;
public:
	Particle *p1, *p2;

	Constraint(Particle* p1, Particle* p2){
		this->p1 = p1;
		this->p2 = p2;

		vec3 vec = p1->getPos() - p2->getPos();
		rest_distance = vec.Length();
	}

	void satisfyConstraint(){
		vec3 p12p2 = p2->getPos() - p1->getPos();
		float currentDistance = p12p2.Length();
		vec3 correction = p12p2*(1 - rest_distance / currentDistance);
		vec3 cHalf = correction*0.5;
		
		if (currentDistance > rest_distance*.75){
			p1->addForce(cHalf);
			p2->addForce(cHalf*-1);
		}
			//p1->offsetPos(cHalf);
			//p2->offsetPos(cHalf*-1);
		
	}

};
class Cloth:public GameObject{
private:
	int nWidth;
	int nHeight;

	vector<Particle> particles;
	vector<Constraint> constraints;
	
	vector<Vertex> vertices;
	vector<int> indices;

	Particle* getParticle(int x, int y){
		return &particles[y*nWidth + x];
	}
	void makeConstraint(Particle*p1, Particle*p2){
		constraints.push_back(Constraint(p1, p2));
	}
	vec3 calcTriangleNormal(Particle *p1, Particle *p2, Particle *p3)
	{
		vec3 pos1 = p1->getPos();
		vec3 pos2 = p2->getPos();
		vec3 pos3 = p3->getPos();

		vec3 v1 = pos2 - pos1;
		vec3 v2 = pos3 - pos1;

		return v1.Cross(v2);
	}

	void addWind(Particle* p1, Particle *p2, Particle* p3, const vec3 dir){
		vec3 normal = calcTriangleNormal(p1, p2, p3);
		vec3 d = normal.Normalized();
		vec3 force = normal*(d.Dot(dir));
		p1->addForce(force);
		p2->addForce(force);
		p3->addForce(force);
	}

	void addTriangle(Particle *p1, Particle*p2, Particle *p3,vec3 color){
		int s=vertices.size();
		vertices.push_back(Vertex(p1->getPos(), p1->getNormal(), color));
		vertices.push_back(Vertex(p2->getPos(), p2->getNormal(), color));
		vertices.push_back(Vertex(p3->getPos(), p3->getNormal(), color));

		indices.push_back(s);
		indices.push_back(s + 1);
		indices.push_back(s + 2);

	}
public:
	double e = 0;
	virtual void Input(){

	}
	void Update()
	{
		e += Time::getDelta();
		int w = e;
		addForce(vec3(0, -0.2, 0)*0.1999);
		if (w%2==0)
			windForce(vec3(0, 0, -.2));
		else
			windForce(vec3(0.2, 0, 0));
		vector<Constraint>::iterator cons;
		for (int i = 0; i < 1; i++){
			for (cons = constraints.begin(); cons != constraints.end(); cons++){
				(*cons).satisfyConstraint();
			}
		}
		for (int i = 0; i < particles.size(); i++){
			particles[i].timeStep();
			
		}
	}
	virtual void Render(){
		vertices.clear();
		indices.clear();
		vec3 color;
		for (int i = 0; i < nWidth - 1; i++){
			for (int j = 0; j < nHeight - 1; j++){
				
				if (i % 2){
					color = vec3(0.6f, 0.2f, 0.2f);
				}else
					color = vec3(1.0f, 1.0f, 1.0f);
				addTriangle(getParticle(i + 1, j), getParticle(i, j), getParticle(i, j + 1),color);
				addTriangle(getParticle(i + 1, j + 1), getParticle(i + 1, j), getParticle(i, j + 1),color);
			}
		}
		Geometry *gm = new Geometry(&vertices[0], &indices[0], vertices.size(), indices.size(), new VertexDescription(),true);
		
		if (this->RenderComponent == NULL){
			BasicMaterial* mat = new BasicMaterial();
			Mesh* msh = new Mesh(gm, mat);
			
			msh->getMaterial()->setShader(new BasicShader());
			this->setRenderComponent(new ObjectRenderer(msh));
			
		}
		else{
			ObjectRenderer* objren = (ObjectRenderer*)this->RenderComponent;
			((BasicMaterial*)objren->getMesh(0)->getMaterial())->setTexture((Texture*)ResourceManager::getInstance()->getResource("acFlag"));
			objren->getMesh(0)->updateGeometry(gm);

		}
		Engine::getEngine()->getRenderer()->drawGameObject(this);
	}
	Cloth(int w, int h, int nw, int nh){
		nWidth = nw;
		nHeight = nh;
		particles.resize(nw*nh);
		this->RenderComponent = NULL;

		for (int i = 0; i < nw; i++){
			for (int j = 0; j < nh; j++){
				vec3 pos = vec3(w *(i / (float)nw), -h *(j / (float)nh), 0);
				particles[j*nw + i] = Particle(pos);
			}
		}

		for (int i = 0; i < nw; i++){
			for (int j = 0; j < nh; j++){
				if (i < nw - 1)makeConstraint(getParticle(i, j), getParticle(i + 1, j));
				if (j < nh - 1)makeConstraint(getParticle(i, j), getParticle(i, j+1));
				if (i < nw - 1 && j<nh-1)makeConstraint(getParticle(i, j), getParticle(i + 1, j+1));
				if (i < nw - 1 && j<nh-1)makeConstraint(getParticle(i+1, j), getParticle(i, j+1));
			}
		}

		for (int i = 0; i < nw; i++){
			for (int j = 0; j < nh; j++){
				if (i < nw - 2)makeConstraint(getParticle(i, j), getParticle(i + 2, j));
				if (j < nh - 2)makeConstraint(getParticle(i, j), getParticle(i, j + 2));
				if (i < nw - 2 && j<nh - 2)makeConstraint(getParticle(i, j), getParticle(i + 2, j + 2));
				if (i < nw - 2 && j<nh - 2)makeConstraint(getParticle(i + 2, j), getParticle(i, j + 2));
			}
		}

		for (int i = 0; i < 3; i++){
			getParticle(0 + i, 0)->offsetPos(vec3(0.5, 0, 0));
			getParticle(0 + i, 0)->makeUnmovable();

			getParticle(0 + i, 0)->offsetPos(vec3(-0.5, 0, 0));
			getParticle(nw - 1 - i, 0)->makeUnmovable();
		}

	}
	void addForce(vec3 dir){
		for (int i = 0; i < particles.size(); i++){
			particles[i].addForce(dir);
			
		}
	}
	void windForce(const vec3 direction)
	{
		for (int x = 0; x<nWidth - 1; x++)
		{
			for (int y = 0; y<nHeight - 1; y++)
			{
				addWind(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), direction);
				addWind(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), direction);
			}
		}
	}

};
#endif