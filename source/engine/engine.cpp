#include "engine/engine.hpp"
#include <algorithm>
#include <chrono>

int32_t Engine::Run() {
  /*
    framework.update();
    systems.update();
    application.update();
  */
  using std::chrono::literals;
  using hrclock = std::chrono::high_resolution_clock;
  using timepoint_t = std::chrono::time_point<clock>;
  std::array<timepoint_t, 2> _time{hrclock::now()-16ms, hrclock::now()-32ms};

  while(_running) {
    std::swap(_time[0], _time[1]);
    _time[0] = hrclock::now();
    const std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(_time[0]-_time[1]);

    framework.update(t, delta);
    systems.update(t, delta);
    applicaiton.update(t,delta);
  }
}