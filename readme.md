# Entity Component System

Simple header-only ECS written in C++17

## Usage

There's `ecs/Demo.hpp` file showcasing the usage of this library.

Create some component
```
struct Gravity
{
	float force;
};
```

Register it using `Registry` instance:
```
registry.RegisterComponent<Gravity>();
```

Implement derived `System` class and register it
```
auto physicsSystem = registry.RegisterSystem<PhysicsSystem>();
```

Set signature for a system. The `Registry` will automatically add related entities to your system using system's signature
```
Signature signature;
signature.set(registry.GetComponentType<Gravity>());
signature.set(registry.GetComponentType<RigidBody>());
signature.set(registry.GetComponentType<Transform>());

registry.SetSystemSignature<PhysicsSystem>(signature);
```

Construct entity and set some components to it:
```
auto entity = registry.ConstructEntity();

registry.AddComponent(entity, Gravity{randGravity(generator)});
```