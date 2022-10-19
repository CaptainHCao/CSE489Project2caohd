#pragma once
class GameTime
{
public:
	static float delta_Time;

	static void Time_Update();

private:

	static double lastRenderTime;
	static double currentTime;
};

