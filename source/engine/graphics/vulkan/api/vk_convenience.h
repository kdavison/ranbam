#pragma once
#include  <type_traits>

namespace vk {
namespace _impl {
template<typename T, typename TAG>
using enable_if_same_t = std::enable_if_t<std::is_same<T, TAG>::value, T>;
}
}
