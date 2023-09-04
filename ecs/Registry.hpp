#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <memory>

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

namespace ecs
{

class Registry
{
private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;

public:
	Registry()
    : componentManager{std::make_unique<ComponentManager>()},
      entityManager{std::make_unique<EntityManager>()},
      systemManager{std::make_unique<SystemManager>()}
	{ }

	Entity ConstructEntity()
	{
		return entityManager->Construct();
	}

	void DestroyEntity(Entity entity)
	{
		entityManager->Destroy(entity);

		componentManager->EntityDestroyed(entity);
		systemManager->EntityDestroyed(entity);
	}

	template<typename T>
	void RegisterComponent()
	{
		componentManager->Register<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		componentManager->Add<T>(entity, component);

		entityManager->GetSignature(entity).set(componentManager->GetType<T>(), true);
		systemManager->EntitySignatureChanged(entity, entityManager->GetSignature(entity));
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		componentManager->Remove<T>(entity);

		entityManager->GetSignature(entity).set(componentManager->GetType<T>(), false);
		systemManager->EntitySignatureChanged(entity, entityManager->GetSignature(entity));
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return componentManager->Get<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return componentManager->GetType<T>();
	}

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return systemManager->Register<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		systemManager->SetSignature<T>(signature);
	}
};

}

#endif