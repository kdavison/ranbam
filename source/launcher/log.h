#pragma once

#include <fstream>
#include <mutex>
#include <string>
#include <cstdint>

namespace ranbam::launcher
{
class Log
{
public:
  Log(const std::string& filepath);
  ~Log();
  void write(const std::string& data);
  void write(const char* data, const std::size_t size);
  void flush();
private:
  std::mutex _mutex;
  std::ofstream _file;
};
}
