#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include"Transform.h"
#include"Component.h"
#include<vector>
using namespace std;
class GameObject{
public:
	GameObject(const Transform trans = Transform());

	void Input();
	void Update();
	void Render();

	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	void removeChild(int ix);

	int childrenCount();
	GameObject* getChild(int ix);

	Transform getTransform();

	void setTransform(const Transform trans);
	void setRenderComponent( Component* val);
	void setBehaviorComponent( Component* val);

	Component getRenderComponent();
	Component getBehaviorComponent();
	~GameObject();
	
private:
	Transform transform;
	vector<GameObject*> childList;
	Component *RenderComponent,*BehaviorComponent;
};
#endif