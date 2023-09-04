#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <unordered_map>

#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

namespace ecs
{

class SystemManager
{
private:
	std::unordered_map<const char*, Signature> signatures{};

	std::unordered_map<const char*, std::shared_ptr<System>> systems{};

public:
	template<typename T>
	std::shared_ptr<T> Register()
	{
		auto typeName = typeid(T).name();

		assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

    auto system = std::make_shared<T>();
    systems.emplace(typeName, system);

		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		auto typeName = typeid(T).name();

		assert(systems.find(typeName) != systems.end() && "System used before registered.");

		signatures.emplace(typeName, signature);
	}

	void EntityDestroyed(Entity entity)
	{
		for (const auto& [_, system] : systems)
		{
			system->entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (const auto& [type, system] : systems)
		{
			if ((entitySignature & signatures[type]) == signatures[type])
			{
				system->entities.insert(entity);
        continue;
			}
			
      system->entities.erase(entity);
		}
	}
};

}

#endif