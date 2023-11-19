#pragma once

namespace ranbam {
  class NonCopyable {
  public:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable(NonCopyable &&) noexcept = default;
    NonCopyable &operator=(const NonCopyable &) = delete;
    NonCopyable &operator=(NonCopyable &) noexcept = default;
  protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;
  };
}