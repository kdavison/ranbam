#include "log.h"
#include <cassert>

namespace ranbam::launcher
{
Log::Log(const std::string& filepath)
  : _mutex()
  , _file(filepath)
{
  assert(_file.is_open());
}

Log::~Log() {
  std::lock_guard<decltype(_mutex)> lock(_mutex);
  if(_file.is_open()) {
    _file.flush();
    _file.close();
  }
}

void Log::write(const std::string& data) {
  std::lock_guard<decltype(_mutex)> lock(_mutex);
  _file.write(data.data(), data.length());
}

void Log::write(const char* data, const std::size_t size) {
  std::lock_guard<decltype(_mutex)> lock(_mutex);
  _file.write(data, size);
}

void Log::flush() {
  std::lock_guard<decltype(_mutex)> lock(_mutex);
  _file.flush();
}
}
