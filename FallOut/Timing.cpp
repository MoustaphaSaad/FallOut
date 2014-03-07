#include"Timing.h"
#include<Windows.h>
#include<iostream>
using namespace std;

double Time::g_Freq=0;
double Time::g_Delta=0;
double Time::g_Elapsed=0;
double Time::frameLimit=1.0/750;
int Time::frameCount=0;
double Time::frameTimeCount=0;
double Time::timeCount=0;
double Time::lastTime=0;


void Time::init(){
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		cout<<"Error: Timing Can't be initialized"<<endl;
	g_Freq = double(li.QuadPart);
	g_Delta = 0;
	g_Elapsed = 0.0f;

	frameLimit =1.0/750;
	frameCount=0;
	frameTimeCount = 0.0;
	timeCount = 0.0;
	lastTime = getTime();
}

void Time::update(double delta){
	g_Delta = delta;
	g_Elapsed += delta;
}

double Time::getTime(){
	LARGE_INTEGER li;
	if(!QueryPerformanceCounter(&li))
		cout<<"Error: Timing Can't be initialized"<<endl;
	return double(li.QuadPart)/g_Freq;
}
double Time::getDelta(){
	return g_Delta;
}

double Time::getElapsedTime(){
	return g_Elapsed;
}