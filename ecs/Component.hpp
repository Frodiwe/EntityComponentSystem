#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <bitset>

namespace ecs
{

using ComponentType = std::uint8_t;
constexpr ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

}

#endif