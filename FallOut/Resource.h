#ifndef Resource_H
#define Resource_H

#include<string>
#include<memory>
#include<Windows.h>
#include"resource1.h"
using namespace std;
namespace Fallout{
	class Resource;
	typedef tr1::shared_ptr<Resource> ResourcePtr;
class Resource{
public:
	enum Type{TEXTURE,MATERIAL,SHADER,MESH,UNDEFINED};
	Resource();
	Resource(string name,Resource::Type t);
	~Resource();

	void setName(string val);
	void setType(Resource::Type val);

	string getName();
	static string loadFile(int name,int type){
		DWORD size;
		const char* data = NULL;
		HRSRC rc = FindResource(NULL,MAKEINTRESOURCE(name),MAKEINTRESOURCE(type));
		HGLOBAL rcData = LoadResource(NULL,rc);
		size = SizeofResource(NULL,rc);
		data = static_cast<const char*>(LockResource(rcData));
		return string(data);
	}
	Resource::Type getType();
protected:
	string name;
	Resource::Type type;
};
}
#endif