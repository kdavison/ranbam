#pragma once

#include <chrono>

namespace ranbam
{
typedef std::chrono::high::high_resolution_clock clock;
typedef std::chrono::timepoint<clock> timepoint;
typedef std::chrono::microseconds microseconds;
}