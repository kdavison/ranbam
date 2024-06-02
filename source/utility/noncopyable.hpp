#pragma once

namespace ranbam {
class noncopyable {
public:
  noncopyable(const noncopyable &) = delete;
  noncopyable(noncopyable &&) noexcept = default;
  noncopyable &operator=(const noncopyable &) = delete;
  noncopyable &operator=(noncopyable &) noexcept = default;
protected:
  noncopyable() = default;
  virtual ~noncopyable() = default;
};
}