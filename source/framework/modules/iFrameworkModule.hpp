#pragma once

#include "utility/time.hpp"

namespace ranbam
{
namespace framework
{
class iFrameworkModule
{
public:
  iFrameworkModule() = default;
  virtual ~iFrameworkModule() = default;
public:
  virtual void update(const ::ranbam::timepoint& t, const ::ranbam::microseconds& delta) = 0;
};
}
}