#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include"VisualObject.h"
#include"Transform.h"
#include"ObjectRenderer.h"
#include"ObjectBehavior.h"

#include<vector>
#include<map>
using namespace std;
struct TimeStep;
class GameObject:public Transformable,public GameComponent{
	friend class RenderEngine;
public:
	GameObject(Transform* trans=new Transform());

	virtual void Input();
	virtual void Update(TimeStep time);
	virtual void Render();

	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	void removeChild(int ix);

	int childrenCount();
	GameObject* getChild(int ix);

	void addComponent(string name,GameComponent* component);
	GameComponent* getComponent(string name);

	~GameObject();
	
protected:
	vector<GameObject*> childList;
	map<string, GameComponent*> GCmap;
};
#endif