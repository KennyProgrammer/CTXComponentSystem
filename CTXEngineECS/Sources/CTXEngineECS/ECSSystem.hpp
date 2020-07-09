#pragma once

#include "CTXEngine/Core/Delta.h"
#include "CTXEngineECS/ECSComponent.hpp"

using namespace CTXEngine::Core;

namespace CTXEngine::ECS
{
	/*
		This class represnets a base set of components, we calls it a 'System'.
	*/
	class BaseSystem
	{	
		private:
			/*Gets type of each component as type identifier.*/
			ArrayList<uint> componentTypes;

		public:
			/*Base constructor.*/
			BaseSystem(const ArrayList<uint>& componentTypesIn)
				: componentTypes(componentTypesIn) 
			{}

			/*Updates all set of components in this system.*/
			virtual void updateComponents(Delta delta, BaseComponent** components) = 0;
			/*Return the component types.*/
			virtual const ArrayList<uint> getComponentTypes() { return componentTypes; }
	};
}