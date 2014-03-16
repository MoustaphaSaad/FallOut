#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include"VisualObject.h"
#include"Transform.h"
#include"ObjectRenderer.h"
#include"ObjectBehavior.h"

#include<vector>
using namespace std;
class GameObject:public Transformable,public Updatable,public Renderable{
	friend class RenderEngine;
public:
	GameObject(Transform* trans=new Transform());

	virtual void Input();
	virtual void Update();
	virtual void Render();

	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	void removeChild(int ix);

	int childrenCount();
	GameObject* getChild(int ix);

	void setRenderComponent( ObjectRenderer* val);
	void setBehaviorComponent( ObjectBehavior* val);

	Renderable getRenderComponent();
	Updatable getBehaviorComponent();
	~GameObject();
	
protected:
	vector<GameObject*> childList;
	Renderable *RenderComponent;
	Updatable *BehaviorComponent;
};
#endif