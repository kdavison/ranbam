#pragma once

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <functional>
#include <vector>
#include <system_error>
#include <cstdint>

namespace ranbam::launcher
{
class pipe
{
public:
  typedef std::function<void(const std::error_code,  std::size_t)> handler_t;
  typedef std::function<void(const char*, const std::size_t)> callback_t;
public:
  pipe(const std::size_t n, ::boost::asio::io_service &ios);

  ::boost::process::async_pipe& operator()() { return _pipe; }

  void read(const callback_t& callback);

  void close();

private:
  std::vector<char> _raw;
  ::boost::asio::mutable_buffer _buffer;
  ::boost::process::async_pipe _pipe;
  handler_t _handler;
};
}
