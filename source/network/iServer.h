#pragma once

#include <stdint.h>

namespace ranbam
{
namespace network
{
class iServer {
public:
  iServer() {}
  virtual ~iServer() {}
  virtual void run() = 0;
  virtual void broadcast() = 0;
  virtual void send() = 0;
  virtual void receive() = 0;
};
}
}
