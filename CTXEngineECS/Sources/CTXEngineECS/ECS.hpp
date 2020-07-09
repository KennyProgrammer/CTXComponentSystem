#pragma once

#include "CTXEngine/Core/CoreBase.h"
#include "CTXEngine/Math/Math.h"
#include "CTXEngineECS/ECSComponent.hpp"
#include "CTXEngineECS/ECSSystem.hpp"

#include "iostream"

namespace CTXEngine::ECS
{
	/*
		Class for groups all Entity Component System and setup.
	*/
	class ECS
	{
		private:
			/*Array list with all systems.*/
			ArrayList<BaseSystem*> systems;
			/*Map  with all components and their identifiers.*/
			Map<uint, ArrayList<uint8>> components;
			/*Array list with all gameObjects.*/
			ArrayList<std::pair<uint, ArrayList<std::pair<uint, uint>>>*> gameObjects;

		public:
			ECS() {};
			~ECS();

			/*Add new Component to GameObject handle.*/
			template<class Component>
			inline void addComponent(GameObjectHandle gameObject, Component* component);
			/*Remove existing Component from GameObject handleand memory.*/
			template<class Component>
			inline bool removeComponent(GameObjectHandle gameObject);
			/*Return existing Component form GameObject handle.*/
			template<class Component>
			inline Component* getComponent(GameObjectHandle gameObject);
			/*Add new GameObject with all components to GameObjectHandle.*/
			GameObjectHandle addGameObject(BaseComponent* components, const uint* componentsIds, size_t numComponents);
			/*Remove existing GameObject with all components from GameObjectHandle and memory.*/
			void removeGameObject(GameObjectHandle handle);
			/*Add new System.*/
			void addSystem(BaseSystem& system);
			/*Remove existing System from memory.*/
			bool removeSystem(BaseSystem& system);
			/*Update all systems with components.*/
			void updateSystems(Delta delta);
		private:
			std::pair<uint, ArrayList<std::pair<uint, uint>>>* handleToRawType(GameObjectHandle handle);
			ArrayList<std::pair<uint, uint>>& handleGameObject(GameObjectHandle handle);
			uint handleGameObjectIndex(GameObjectHandle handle);
			void deleteComponent(uint componentId, uint index);
			void addComponentInternal(GameObjectHandle handle, ArrayList<std::pair<uint, uint>>& gameObject, uint componentId, BaseComponent* component);
			bool removeComponentInternal(GameObjectHandle handle, uint componentId);
			BaseComponent* getComponentInternal(ArrayList<std::pair<uint, uint>>& gameObjectComponents, ArrayList<uint8>& array, uint componentId);
			void updateSytstemWithMultipieComponents(uint index, Delta delta, const ArrayList<uint>& componentTypes, ArrayList<BaseComponent*>& componentParam, ArrayList<ArrayList<uint8>*>& componentArrays);
			uint32 findLeastCommonComponent(const ArrayList<uint32>& componentTypes);
			//NULL_COPY_AND_ASSIGN(ECS);
	};

	/*
		Add new Component to GameObject handle.
	*/
	template<class Component>
	inline void ECS::addComponent(GameObjectHandle gameObject, Component* component)
	{
		this->addComponentInternal(gameObject, this->handleGameObject(gameObject), Component::id, component);
	}

	/*
		Remove existing Component from GameObject handle and memory.
	*/
	template<class Component>
	inline bool ECS::removeComponent(GameObjectHandle gameObject)
	{
		return this->removeComponentInternal(gameObject, Component::id);
	}

	/*
		Return existing Component form GameObject handle.
	*/
	template<class Component>
	inline Component* ECS::getComponent(GameObjectHandle gameObject)
	{
		this->getComponentInternal(this->handleGameObject(gameObject), this->components[Component::Id], Component::Id);
	}
}