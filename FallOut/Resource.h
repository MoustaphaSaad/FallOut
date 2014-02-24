#ifndef Resource_H
#define Resource_H
#include<string>
using namespace std;
enum ResourceType{TEXTURE,MATERIAL,SHADER,MESH,UNDEFINED};
class Resource{
public:
	Resource();
	Resource(string name,ResourceType t);
	~Resource();

	void setName(string val);
	void setType(ResourceType val);

	string getName();
	ResourceType getType();
protected:
	string name;
	ResourceType type;
};
#endif