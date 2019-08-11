#include "pipe.h"

namespace ranbam::launcher
{
pipe::pipe(const std::size_t n, ::boost::asio::io_service& ios)
  : _raw(n)
  , _buffer(_raw.data(), _raw.size())
  , _pipe(ios)
{
}

void pipe::read(const callback_t &callback) {
  assert(callback);
  _handler = [&](const std::error_code &ec, std::size_t n) {
    if(callback) callback(_raw.data(), n);
    if(!ec) {
      ::boost::asio::async_read(_pipe, _buffer, _handler);
    } else {
      std::string error =
        "pipe error (" +
        std::string(ec.category().name()) +
        ")(" +
        std::to_string(ec.value()) +
        ")(" +
        ec.message() +
        ")\n";
      if(callback) callback(error.data(), error.length());
    }
  };
  ::boost::asio::async_read(_pipe, _buffer, _handler);
}

void pipe::close() {
  _pipe.close();
}

}
