#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstddef>
#include <cstdint>

namespace ecs
{

using Entity = std::uint32_t;
constexpr std::size_t MAX_ENTITIES = 5000;

}

#endif