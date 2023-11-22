#pragma once

#include <thread>

namespace UTILITY
{
static const std::thread::id MAIN_THREAD = std::this_thread::get_id();

static bool IsMainThread() {
  return (std::this_thread::get_id() == MAIN_THREAD);
}


} //::UTILITY
