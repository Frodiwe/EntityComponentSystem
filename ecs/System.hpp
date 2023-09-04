#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <unordered_set>

#include "Entity.hpp"

namespace ecs
{

class System
{
  friend class SystemManager;

protected:
  std::unordered_set<Entity> entities;
};

}

#endif