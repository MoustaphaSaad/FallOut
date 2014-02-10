#ifndef Resource_H
#define Resource_H
#include<string>
using namespace std;
enum ResourceType{TEXTURE,MATERIAL,SHADER,MESH};
class Resource{
public:
	Resource(string name,ResourceType t);
	~Resource();

	string getName();
	ResourceType getType();
protected:
	string name;
	ResourceType type;
};
#endif