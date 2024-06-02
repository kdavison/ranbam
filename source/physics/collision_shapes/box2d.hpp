#pragma once

#include "math/vector.hpp"
#include <array>

namespace ranbam
{
namespace physics
{
template<typename T>
class box2d {
public:
  box2d();

  virtual bool is_inside(const math::Vector2<T>& point) const;

private:
  std::array<math::Vector2<T>, 4> _points;
};
}
}