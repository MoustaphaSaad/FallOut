#ifndef TIMING_H
#define TIMING_H
enum FPS{UNLIMITED,LIMITED};
struct TimeStep{
	double delta;
	double ElapsedTime;
	TimeStep(double d, double e){
		delta = d;
		ElapsedTime = e;
	}
};
class Time{
	friend class Engine;

	static const long NANO_PER_SEC = 1000000000L;
	static double g_Freq,g_Delta,g_Elapsed;
	static double frameLimit;
	static int frameCount;
	static double frameTimeCount, timeCount, lastTime, ElapsedTime;
	static FPS type;
public:
	static void init();
	static double getTime();
	static void setType(FPS val);
	static FPS getType();
	static void setFrameLimit(double val){
		Time::frameLimit = 1/val;
	}
	static double getFrameLimit(){
		return 1/Time::frameLimit;
	}

	static void update(double delta);

	static double getDelta();
	static double getElapsedTime();
};
#endif