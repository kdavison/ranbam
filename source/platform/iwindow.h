#pragma once
#include <math/vector.hpp>


namespace ranbam
{
namespace platform
{
class iWindow {
public:
  typedef dimensions_t ::ranbam::Vector2<int32_t>;
  typedef position_t ::ranbam::Vector2<int32_t>;
public:
  virtual ~iWindow() = default;

  virtual dimensions_t size() = 0;
  virtual void size(const dimensions_t &dimensions) = 0;

  virtual position_t position() = 0;
  virtual void position_t(const position_t &position) = 0;

  virtual void show() = 0;
  virtual void hide() = 0;
};
}
}
