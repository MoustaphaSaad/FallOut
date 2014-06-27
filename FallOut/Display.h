#ifndef DISPLAY_H
#define DISPLAY_H
#include<string>
#include<memory>
using namespace std;
namespace Fallout{
	struct Display;
	typedef tr1::shared_ptr<Display> DisplayPtr;
struct Display
{
public:
	int width,height;
	string title;
	Display(){
		width = 0;
		height = 0;
		title="";
	}
	Display(int w,int h,string title){
		width = w;
		height = h;
		this->title = title;
	}
	float getAspect(){
		return (float)width/(float)height;
	}
	static void BindTarget();
};
}
#endif