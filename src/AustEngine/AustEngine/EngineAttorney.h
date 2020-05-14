#pragma once

#include "AustEngine.h"

class EngineAttorney
{
public:
	class AustTime
	{
		friend class TimeManager;
		friend class FreezeTime;
	private:
		static float EngineTime() { return AustEngine::Instance().GetTimeInSeconds(); }
	};
	class AustWindowSize
	{
		friend class CameraManager;
	private:
		static int GetWidth() { return AustEngine::Instance().getWidth(); }; 
		static int GetHeight() { return AustEngine::Instance().getHeight(); };
	};
};