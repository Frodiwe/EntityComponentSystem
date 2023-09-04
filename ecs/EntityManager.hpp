#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <queue>
#include <array>

#include "Entity.hpp"
#include "Component.hpp"

namespace ecs
{

class EntityManager
{
private:
	std::queue<Entity> entities;

	std::array<Signature, MAX_ENTITIES> signatures;

	uint32_t livingEntityCount;

public:
	EntityManager()
	{
		for (auto entity = Entity{0}; entity < MAX_ENTITIES; ++entity)
		{
			entities.push(entity);
		}
	}

	Entity Construct()
	{
		assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		Entity id = entities.front();
		entities.pop();

		++livingEntityCount;

		return id;
	}

	void Destroy(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		signatures[entity].reset();
		entities.push(entity);

		--livingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		signatures[entity] = signature;
	}

	Signature& GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		return signatures[entity];
	}
};

}

#endif