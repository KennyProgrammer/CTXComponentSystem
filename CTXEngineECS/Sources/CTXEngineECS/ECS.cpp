#include "CTXEngineECS/ECS.hpp"

namespace CTXEngine::ECS
{
	/*
		Default destructor.
	*/
	ECS::~ECS()
	{
		for (Map<uint, ArrayList<uint8>>::iterator itr = components.begin(); itr != components.end(); ++itr)
		{
			size_t typeSize = BaseComponent::getTypeSize(itr->first);
			ComponentDestroyFunc destroyFunc = BaseComponent::getTypeDestroyFunc(itr->first);
			for (uint i = 0; i <  itr->second.size(); i += (uint) typeSize)
				destroyFunc((BaseComponent*)&itr->second[i]);
		}

		for (uint i = 0; i < this->gameObjects.size(); i++)
			delete this->gameObjects[i];
	}

	/*
		Add new GameObject with all components to GameObjectHandle.
	*/
	GameObjectHandle ECS::addGameObject(BaseComponent* components, const uint* componentsIds, size_t numComponents)
	{
		std::pair<uint, ArrayList<std::pair<uint, uint>>>* gameObject = new 
			std::pair<uint, ArrayList<std::pair<uint, uint>>>();
		GameObjectHandle handle = (GameObjectHandle)gameObject;
		for (uint i = 0; i < numComponents; i++)
		{
			if (!BaseComponent::isTypeValid(componentsIds[i]))
			{
				std::cout << componentsIds[i] << " is not valid component type!" << std::endl;
				delete gameObject;
				return CTX_NULL_GAMEOBJECT_HANDLE;
			}

			//check if component id is actually valid.
			this->addComponentInternal(handle, gameObject->second, componentsIds[i], &components[i]);
		}

		gameObject->first = (uint) this->gameObjects.size();
		this->gameObjects.push_back(gameObject);
		return handle;
	}

	/*
		Remove existing GameObject with all components from GameObjectHandle and memory.
	*/
	void ECS::removeGameObject(GameObjectHandle handle)
	{
		ArrayList<std::pair<uint, uint>>& gameObject = handleGameObject(handle);
		for (uint i = 0; i < this->gameObjects.size(); i++)
			this->deleteComponent(gameObject[i].first, gameObject[i].second);

		//current index
		uint destIndex = this->handleGameObjectIndex(handle);
		uint srcIndex = (uint)gameObjects.size() - 1;
		delete gameObjects[destIndex];

		//moving the last GameObject in the list to where the GameObject we deleting is.
		this->gameObjects[destIndex] = this->gameObjects[srcIndex];
		this->gameObjects.pop_back();
	}

	/*
		Add new System.
	*/
	void ECS::addSystem(BaseSystem& system)
	{
		systems.push_back(&system);
	}

	/*
		Remove existing System from memory.
	*/
	bool ECS::removeSystem(BaseSystem& system)
	{
		for (uint i = 0; i < this->systems.size(); i++)
		{
			if (&system == this->systems[i])
			{
				this->systems.erase(systems.begin() + i);
				return true;
			}
		}
		return false;
	}

	/*
		Update all systems with all components in it..
	*/
	void ECS::updateSystems(Delta delta)
	{
		ArrayList<BaseComponent*> componentParam;
		ArrayList<ArrayList<uint8>*> componentArrays;
		for (uint i = 0; i < this->systems.size(); i++)
		{
			const ArrayList<uint>& componentTypes = this->systems[i]->getComponentTypes();
			if (componentTypes.size() == 1)
			{
				size_t typeSize = BaseComponent::getTypeSize(componentTypes[0]);
				ArrayList<uint8>& arr = components[componentTypes[0]];
				for (uint j = 0; j < arr.size(); j += typeSize)
				{
					BaseComponent* component = (BaseComponent*)&arr[j];
					this->systems[i]->updateComponents(delta, &component);
				}
			}
			else
			{
				this->updateSytstemWithMultipieComponents(i, delta, componentTypes, componentParam, componentArrays);
			}
		}
	}

	////////////////////////////////////
	//Utility private functions-handles.
	////////////////////////////////////

	std::pair<uint, ArrayList<std::pair<uint, uint>>>* ECS::handleToRawType(GameObjectHandle handle)
	{
		return (std::pair<uint, ArrayList<std::pair<uint, uint>>>*)handle;
	}

	uint ECS::handleGameObjectIndex(GameObjectHandle handle)
	{
		return this->handleToRawType(handle)->first;
	}

	ArrayList<std::pair<uint, uint>>& ECS::handleGameObject(GameObjectHandle handle)
	{
		return this->handleToRawType(handle)->second;
	}

	void ECS::deleteComponent(uint componentId, uint index)
	{
		ArrayList<uint8>& array = this->components[componentId];
		ComponentDestroyFunc destroyFunc = BaseComponent::getTypeDestroyFunc(componentId);
		size_t typeSize = BaseComponent::getTypeSize(componentId);
		uint srcIndex = (uint) (array.size() - typeSize);

		BaseComponent* destComponent = (BaseComponent*) &array[index];
		BaseComponent* srcComponent =  (BaseComponent*) &array[srcIndex];
		destroyFunc(destComponent);

		if (index == srcIndex)
		{
			array.resize(srcIndex);
			return;
		}

		memcpy(destComponent, srcComponent, typeSize);
		
		ArrayList<std::pair<uint, uint>>& srcComponents = this->handleGameObject(srcComponent->gameObject);
		for (uint i = 0; i < srcComponents.size(); i++)
		{
			if (componentId == srcComponents[i].first && srcIndex == srcComponents[i].second)
			{
				srcComponents[i].first = index;
				break; 
			}
		}

		array.resize(srcIndex);
	}

	void ECS::addComponentInternal(GameObjectHandle handle, ArrayList<std::pair<uint, uint>>& gameObject, uint componentId, BaseComponent* component)
	{
		ComponentCreateFunc createFunc = BaseComponent::getTypeCreateFunc(componentId);
		std::pair<uint, uint> newPair;
		newPair.first = componentId;
		newPair.second = createFunc(this->components[componentId], handle, component);
		gameObject.push_back(newPair);
	}

	bool ECS::removeComponentInternal(GameObjectHandle handle, uint componentId)
	{
		ArrayList<std::pair<uint, uint>>& gameObjectComponents = this->handleGameObject(handle);
		for (uint i = 0; i < gameObjectComponents.size(); i++)
		{
			if (componentId == gameObjectComponents[i].first)
			{
				this->deleteComponent(gameObjectComponents[i].first, gameObjectComponents[i].second);
				uint srcIndex = (uint) gameObjectComponents.size() - 1;
				uint destIndex = i;
				gameObjectComponents[destIndex] = gameObjectComponents[srcIndex];
				gameObjectComponents.pop_back();
				return true;
			}
		}

		return false;
	}

	BaseComponent* ECS::getComponentInternal(ArrayList<std::pair<uint, uint>>& gameObjectComponents, ArrayList<uint8>& array, uint componentId)
	{
		for (uint i = 0; i < gameObjects.size(); i++)
		{
			if (componentId == gameObjectComponents[i].first)
				return (BaseComponent*)&this->components[componentId][gameObjectComponents[i].second];
		}

		return nullptr;
	}

	void ECS::updateSytstemWithMultipieComponents(uint index, Delta delta, const ArrayList<uint>& componentTypes, 
		ArrayList<BaseComponent*>& componentParam, ArrayList<ArrayList<uint8>*>& componentArrays)
	{
		componentParam.resize(Math::max(componentParam.size(), componentTypes.size()));
		componentArrays.resize(Math::max(componentArrays.size(), componentTypes.size()));
		for (uint32 i = 0; i < componentTypes.size(); i++) 
			componentArrays[i] = &components[componentTypes[i]];
		uint32 minSizeIndex = findLeastCommonComponent(componentTypes);

		size_t typeSize = BaseComponent::getTypeSize(componentTypes[minSizeIndex]);
		ArrayList<uint8>& arr = *componentArrays[componentTypes[minSizeIndex]];
		for (uint i = 0; i < arr.size(); i += typeSize)
		{
			componentParam[minSizeIndex] = (BaseComponent*)&arr[i];
			ArrayList<std::pair<uint, uint>>& gameObjectComponents = this->handleGameObject(componentParam[minSizeIndex]->gameObject);

			bool isValid = true;
			for (uint j = 0; j < componentTypes.size(); j++)
			{
				if (j == 0) continue;

				componentParam[j] = this->getComponentInternal(gameObjectComponents, *componentArrays[j], componentTypes[j]);
				if (componentParam[j] == nullptr)
				{
					isValid = false;
					break;
				}
			}

			if (isValid)
				this->systems[index]->updateComponents(delta, &componentParam[0]);
		}
	}

	uint32 ECS::findLeastCommonComponent(const ArrayList<uint32>& componentTypes)
	{
		uint32 minSize = components[componentTypes[0]].size()
			/ BaseComponent::getTypeSize(componentTypes[0]);
		uint32 minIndex = 0;
		for (uint32 i = 1; i < componentTypes.size(); i++) 
		{
			size_t typeSize = BaseComponent::getTypeSize(componentTypes[i]);
			uint32 size = components[componentTypes[i]].size() / typeSize;
			if (size < minSize) 
			{
				minSize = size;
				minIndex = i;
			}
		}

		return minIndex;
	}
}