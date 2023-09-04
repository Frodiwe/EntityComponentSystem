#ifndef ECS_DEMO_HPP
#define ECS_DEMO_HPP

#include <random>
#include <iostream>

#include "Registry.hpp"
#include "System.hpp"

namespace ecs::demo
{

auto registry = Registry{};

struct Gravity
{
	float force;
};

struct RigidBody
{
	float velocity;
	float acceleration;
};

struct Transform
{
	float position;
	float rotation;
	float scale;
};

class PhysicsSystem : public System
{
public:
  void Update(float dt)
  {
    for (auto const& entity : entities)
    {
      auto& rigidBody = registry.GetComponent<RigidBody>(entity);
      auto& transform = registry.GetComponent<Transform>(entity);
      const auto& gravity = registry.GetComponent<Gravity>(entity);

      transform.position += rigidBody.velocity * dt;
      rigidBody.velocity += gravity.force * dt;

      std::cout << "Position: " << transform.position << ", Velocity: " << rigidBody.velocity << std::endl;
    }
  }
};

void run()
{
	registry.RegisterComponent<Gravity>();
	registry.RegisterComponent<RigidBody>();
	registry.RegisterComponent<Transform>();

	auto physicsSystem = registry.RegisterSystem<PhysicsSystem>();

	Signature signature;
	signature.set(registry.GetComponentType<Gravity>());
	signature.set(registry.GetComponentType<RigidBody>());
	signature.set(registry.GetComponentType<Transform>());
	registry.SetSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	for (auto& entity : entities)
	{
		entity = registry.ConstructEntity();

		registry.AddComponent(entity, Gravity{randGravity(generator)});

		registry.AddComponent(
			entity,
			RigidBody{
				.velocity = 0.f,
				.acceleration = 0.f
			});

		registry.AddComponent(
			entity,
			Transform{
				.position = randPosition(generator),
				.rotation = randRotation(generator),
				.scale = scale
			});
	}

	float dt = 0.0f;

	for (auto i = 0; i < 10; i++)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		physicsSystem->Update(dt);

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}
}

}

#endif