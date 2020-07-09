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
			ComponentCreateFunc createFunc = BaseComponent::getTypeCreateFunc(componentsIds[i]);
			std::pair<uint, uint> newPair;
			newPair.first = componentsIds[i];
			newPair.second = createFunc(this->components[componentsIds[i]], handle, &components[i]);
			gameObject->second.push_back(newPair);
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
			this->removeComponentInternal(gameObject[i].first, gameObject[i].second);

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
	void ECS::removeSystem(BaseSystem& system)
	{
		//auto itr = std::find(systems.begin(), this->systems.end(), system);
		//if (itr != this->systems.end())
		//{
		//	this->systems.erase(itr);
		//}
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

	void ECS::removeComponentInternal(uint componentId, uint index)
	{

	}
}