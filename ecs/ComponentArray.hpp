#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include <unordered_map>

#include "Entity.hpp"
#include "Component.hpp"

namespace ecs
{

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:
	std::array<T, MAX_ENTITIES> components{};

	std::unordered_map<Entity, size_t> entityIndex{};

	std::unordered_map<size_t, Entity> indexEntity{};

	size_t count{};

public:
	void Add(Entity entity, T component)
	{
		assert(entityIndex.find(entity) == entityIndex.end() && "Component added to same entity more than once.");

		entityIndex[entity] = count;
		indexEntity[count] = entity;
		components[count] = component;
		
    ++count;
	}

	void Remove(Entity entity)
	{
		assert(entityIndex.find(entity) != entityIndex.end() && "Removing non-existent component.");

		components[entityIndex[entity]] = components[count - 1];

		entityIndex[indexEntity[count - 1]] = entityIndex[entity];
		indexEntity[entityIndex[entity]] = indexEntity[count - 1];

		entityIndex.erase(entity);
		indexEntity.erase(count - 1);

		--count;
	}

	T& Get(Entity entity)
	{
		assert(entityIndex.find(entity) != entityIndex.end() && "Retrieving non-existent component.");

		return components[entityIndex[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (entityIndex.find(entity) == entityIndex.end())
		{
      return;
		}

    Remove(entity);
	}
};

}

#endif