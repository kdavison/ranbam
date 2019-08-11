#pragma once

namespace ranbam
{
namespace platform
{
class iWindow {
public:
  typedef struct dimensions {
    int32_t width, height;
  } dimensions_t;

public:
  virtual ~iWindow() = default;

  virtual dimensions_t size() = 0;
  virtual void size(const dimensions_t& dims) = 0;
};
}
}
