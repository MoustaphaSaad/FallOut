#ifndef DISPLAY_H
#define DISPLAY_H
#include<string>
using namespace std;
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
};
#endif