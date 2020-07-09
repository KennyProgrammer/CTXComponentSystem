#pragma once

#include "CTXEngine/Core/CoreBase.h"

namespace CTXEngine
{
	namespace Core
	{
		/*
			Delta time describes the time difference between the previous
			frame that was drawn and the current frame in modern game engines
			like Unity or Unreal, but CTXEngine also be used it.
		*/
		class Delta
		{
		private:
			/*To summaries, delta time is usually a variable calculated for us in modern
			game engines that stores the time difference between the last and current frame. */
			float deltaTime = 0.0f;

		public:
			Delta(float timeIn = 0.0f)
				: deltaTime(timeIn)
			{
			}

			/*
				Use this operator to cast Timer object to single float.
			*/
			operator float() const
			{
				return this->deltaTime;
			}

			/*
				Return delta time instance.
			*/
			const float getDeltaTime() const
			{
				return this->deltaTime;
			}

			/*
				Return delta time instance in seconds.
			*/
			float getSeconds() const
			{
				return this->getDeltaTime();
			}

			/*
				Return delta time in milliseconds.
			*/
			float getMilliseconds() const
			{
				return this->getDeltaTime() * 1000.0f;
			}
		};
	}
}