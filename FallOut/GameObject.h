#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include"VisualObject.h"
#include"Transform.h"
#include"ObjectRenderer.h"
#include"ObjectBehavior.h"
#include"VisualComposer.h"
#include<vector>
#include<map>
#include<memory>
using namespace std;
namespace Fallout{
struct TimeStep;
class GameObject:public Transformable,public GameComponent{
	typedef tr1::shared_ptr<GameObject> GameObjectPtr;
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
}
#endif