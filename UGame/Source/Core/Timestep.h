#pragma once
#include "Core.h"

namespace UGame
{
	class UGAME_API Timestep
	{
	public:
		Timestep(float time = 0.f) : time(time)
		{
			
		}

		operator float() const { return time; }
		
		float GetSeconds() const { return time; }
		float GetMilliseconds() const { return time * 1000.f; }
		
	private:
		float time{ 0.f };
	};
}