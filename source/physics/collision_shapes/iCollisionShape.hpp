#pragma once

#include <cstdint>
#include <vector>

namespace ranbam
{
namespace physics
{
template<typename t>
class iCollisionShape2d
{
public:
  virtual std::size_t vertexCount() const = 0;
  virtual std::vector<math::Vector2<T>>& getVertices() const = 0;
  virtual math::Vector2<T> get_centroid() const = 0;
  virtual bool is_inside(const math::Vector2<T>&) const = 0;
};
} 
}