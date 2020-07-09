#include "CTXEngineECS/ECSComponent.hpp"

namespace CTXEngine::ECS
{
	ArrayList<std::tuple<ComponentCreateFunc, ComponentDestroyFunc, size_t>> BaseComponent::componentTypes;

	/*
		This func returns next identifier of Component.
	*/
	uint BaseComponent::registerComponentType(ComponentCreateFunc createFunc,
		ComponentDestroyFunc destroyFunc, size_t size)
	{
		uint componentId = componentTypes.size();
		componentTypes.push_back(std::tuple<ComponentCreateFunc, ComponentDestroyFunc, size_t>
			(createFunc, destroyFunc, size));
		return componentId;
	}

	/*
		Return type of create func.
	*/
	ComponentCreateFunc BaseComponent::getTypeCreateFunc(uint id)
	{
		return std::get<0>(componentTypes[id]);
	}

	/*
		Return type of destroy func.
	*/
	ComponentDestroyFunc BaseComponent::getTypeDestroyFunc(uint id)
	{
		return std::get<1>(componentTypes[id]);
	}

	/*
		Return size of destroy func.
	*/
	size_t BaseComponent::getTypeSize(uint id)
	{
		return std::get<2>(componentTypes[id]);
	}

	/*
		Check on type validation.
	*/
	bool BaseComponent::isTypeValid(uint id)
	{
		return id < componentTypes.size();
	}
}