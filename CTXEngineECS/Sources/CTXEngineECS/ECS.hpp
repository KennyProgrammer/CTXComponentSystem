#pragma once

#include "CTXEngine/Core/CoreBase.h"
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

			/*Add new GameObject with all components to GameObjectHandle.*/
			GameObjectHandle addGameObject(BaseComponent* components, const uint* componentsIds, size_t numComponents);
			/*Remove existing GameObject with all components from GameObjectHandle and memory.*/
			void removeGameObject(GameObjectHandle handle);

			/*Add new Component to handle.*/
			template<class Component>
			void addComponent(GameObjectHandle gameObject, Component* component);

			/*Remove exising Component form handle and memory.*/
			template<class Component>
			void removeComponent(GameObjectHandle gameObject);

			/*Return component form handle.*/
			template<class Component>
			void getComponent(GameObjectHandle gameObject);

			/*Add new System.*/
			void addSystem(BaseSystem& system);
			/*Remove existing System from memory.*/
			void removeSystem(BaseSystem& system);
			/*Update all systems.*/
			void updateSystems(Delta delta);

		private:
			std::pair<uint, ArrayList<std::pair<uint, uint>>>* handleToRawType(GameObjectHandle handle);
			ArrayList<std::pair<uint, uint>>& handleGameObject(GameObjectHandle handle);
			uint handleGameObjectIndex(GameObjectHandle handle);
			void removeComponentInternal(uint componentId, uint index);

			//NULL_COPY_AND_ASSIGN(ECS);
	};
}