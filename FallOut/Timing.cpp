#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif __cplusplus >= 201103L
#define OS_OTHER_CPP11
#else
#define OS_OTHER
#endif
#include"Timing.h"
#ifdef OS_WINDOWS
#include<Windows.h>
#include<sys\timeb.h>
#endif

#ifdef OS_LINUX
#include <sys/time.h>
#endif

#include<iostream>
using namespace std;

double Time::g_Freq=0;
double Time::g_Delta=0;
double Time::g_Elapsed=0;
double Time::frameLimit=1.0/60;
int Time::frameCount=0;
double Time::frameTimeCount=0;
double Time::timeCount=0;
double Time::lastTime=0;
FPS Time::type = FPS::LIMITED;


void Time::init(){
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		cout<<"Error: Timing Can't be initialized"<<endl;
	g_Freq = double(li.QuadPart);
#endif
#ifdef OS_LINUX
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	g_Freq = double(ts.tv_sec);
#endif
	g_Delta = 0;
	g_Elapsed = 0.0f;

	frameLimit = 1.0 / 60;
	frameCount=0;
	frameTimeCount = 0.0;
	timeCount = 0.0;
	lastTime = getTime();
}

void Time::update(double delta){
	g_Delta = delta;
	g_Elapsed += delta;
}
void Time::setType(FPS val){
	Time::type = val;
}
FPS Time::getType(){
	return type;
}

double Time::getTime(){
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	if(!QueryPerformanceCounter(&li))
		cout<<"Error: Timing Can't be initialized"<<endl;
	return double(li.QuadPart)/g_Freq;
#endif
#ifdef OS_LINUX
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (double)(((long)ts.tv_sec * 1000000000L) + ts.tv_nsec) / ((double)(1000000000L));
#endif
}
double Time::getDelta(){
	return g_Delta;
}

double Time::getElapsedTime(){
	return g_Elapsed;
}