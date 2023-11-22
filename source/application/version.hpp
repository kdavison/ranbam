#pragma once

namespace ranbam
{
class Version {
public:
  Version(uint8_t major, uint8_t minor, uint8_t patch)
    : _major(major)
    , _minor(minor)
    , _patch(patch)
  {
  }

  constexpr uint8_t major() {
    return _major;
  }

  constexpr uint8_t minor() {
    return _minor;
  }

  constexpr uint8_t patch() {
    return _patch;
  }

private:
  uint8_t _major, _minor, _patch;
}
}