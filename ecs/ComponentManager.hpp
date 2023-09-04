#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <execution>
#include <algorithm>

#include "ComponentArray.hpp"

namespace ecs
{

class ComponentManager
{
private:
	std::unordered_map<const char*, ComponentType> componentTypes{};

	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

	ComponentType nextComponentType{0};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetArray()
	{
		auto typeName = typeid(T).name();

		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
	}

public:
	template<typename T>
	void Register()
	{
		auto typeName = typeid(T).name();

		assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

		componentTypes.emplace(typeName, nextComponentType);
		componentArrays.emplace(typeName, std::make_shared<ComponentArray<T>>());

		++nextComponentType;
	}

	template<typename T>
	ComponentType GetType()
	{
		auto typeName = typeid(T).name();

		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

		return componentTypes[typeName];
	}

	template<typename T>
	void Add(Entity entity, T component)
	{
		GetArray<T>()->Add(entity, component);
	}

	template<typename T>
	void Remove(Entity entity)
	{
		GetArray<T>()->Remove(entity);
	}

	template<typename T>
	T& Get(Entity entity)
	{
		return GetArray<T>()->Get(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (const auto& [_, component] : componentArrays)
		{
			component->EntityDestroyed(entity);
		}
	}
};

}

#endif