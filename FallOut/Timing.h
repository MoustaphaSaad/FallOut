#ifndef TIMING_H
#define TIMING_H
class Time{
	friend class Engine;

	static const long NANO_PER_SEC = 1000000000L;
	static double g_Freq,g_Delta,g_Elapsed;
	static double frameLimit;
	static int frameCount;
	static double frameTimeCount,timeCount,lastTime;
public:
	static void init();
	static double getTime();

	static void update(double delta);

	static double getDelta();
	static double getElapsedTime();
};
#endif