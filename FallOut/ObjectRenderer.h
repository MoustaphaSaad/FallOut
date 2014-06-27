#ifndef OBJECTRENDERER_H_
#define OBJECTRENDERER_H_
#include"Component.h"
#include"VisualObject.h"
#include"Mesh.h"
#include<vector>
using namespace std;
namespace Fallout{
class DefaultRenderer : public GameComponent{
	friend class GameObject;
public:
	DefaultRenderer(GameObject* parent, Mesh* m);
	DefaultRenderer(GameObject* parent, vector<Mesh*> m);
	DefaultRenderer();
	~DefaultRenderer();

	virtual void Input(){}
	virtual void Update(){}
	virtual void Render();

	Mesh* getMesh(int ix){
		if (ix < Meshes.size())
			return Meshes[ix];
	}

protected:
	vector<Mesh*> Meshes;
};
}
#endif
