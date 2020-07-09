#pragma once

#include "CTXEngine/Core/CoreBase.h"
#include "CTXEngine/Core/Types.hpp"

#define CTX_NULLPTR nullptr
#define CTX_NULL_GAMEOBJECT_HANDLE CTX_NULLPTR

namespace CTXEngine::ECS
{
	struct BaseComponent;
	typedef void* GameObjectHandle;
	typedef uint (*ComponentCreateFunc)(ArrayList<uint8>& memory, GameObjectHandle gameObject, BaseComponent* comp);
	typedef void (*ComponentDestroyFunc)(BaseComponent* comp);

	/*
		Base structure component.
	*/
	struct BaseComponent
	{
		public:
			GameObjectHandle gameObject = CTX_NULL_GAMEOBJECT_HANDLE;

			/*This func returns next identifier of Component.*/
			static uint registerComponentType(ComponentCreateFunc createFunc, 
				ComponentDestroyFunc destroyFunc, size_t size);
			/*Return type of create func.*/
			static ComponentCreateFunc getTypeCreateFunc(uint id);
			/*Return type of destory func.*/
			static ComponentDestroyFunc getTypeDestroyFunc(uint id);
			/*Return type of size.*/
			static size_t getTypeSize(uint id);
			/*Check on type validation.*/
			static bool isTypeValid(uint id);
		private:
			static ArrayList<std::tuple<ComponentCreateFunc, ComponentDestroyFunc, size_t>> componentTypes;
	};

	/*
		This is main component for all runtime / intermedite ECS in hole engine.
	*/
	template<typename T>
	struct Component : public BaseComponent
	{
		static const uint id;
		static const size_t size;
		static const ComponentCreateFunc createFunc;
		static const ComponentDestroyFunc destroyFunc;
	};
	
	/*
		This is behavior of component create function.
	*/
	template<typename Component>
	uint ComponentCreate(ArrayList<uint8>& memory, GameObjectHandle gameObject, BaseComponent* comp)
	{
		uint index = index.size();
		memory.resize(index + Component::size);
		Component* component = new(&memory[index]) Component(*(Component*)comp);
		component->gameObject = gameObject;
		return index;
	}

	/*
		This is behavior of component destroy function.
	*/
	template<typename Component>
	void ComponentDestroy(BaseComponent* comp)
	{
		Component* component = (Component*)comp;
		component->~Component();
	}

	/*
		This identifier of this component.
	*/
	template<typename T>
	const uint Component<T>::id(BaseComponent::registerComponentType(ComponentCreate<T>, ComponentDestroy<T>, sizeof(T)));

	/*
		This size in bytes of this component.
	*/
	template<typename T>
	const size_t Component<T>::size(sizeof(T));

	/*
		This function will be create this component by allocating id and size.
	*/
	template<typename T>
	const ComponentCreateFunc Component<T>::createFunc(ComponentCreate<T>);

	/*
		This function will be destroy this component by free memory.
	*/
	template<typename T>
	const ComponentDestroyFunc Component<T>::destroyFunc(ComponentDestroy<T>);

	struct TestComponent : public Component<TestComponent>
	{
		float x, y;
	};
}