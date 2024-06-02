#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>

using namespace std::literals;

using hrClock = std::chrono::high_resolution_clock;
using timepoint_t = std::chrono::time_point<hrClock>;
using delta_t = std::chrono::microseconds;


void update(const timepoint_t& t, const delta_t& dt) {
  std::time_t time = hrClock::to_time_t(t);
  std::cout << time << " : " << dt.count() << "us" << std::endl;
}

int32_t main(int argc, char *argv[])
{
  std::array<timepoint_t, 2> _time{hrClock::now()-16ms, hrClock::now()-32ms};

  for(std::size_t i(0); i < 100; ++i) {
    std::swap(_time[0], _time[1]);
    _time[0] = hrClock::now();
    const std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(_time[0]-_time[1]);

    update(_time[0], delta);

    std::this_thread::sleep_for(16ms);
  }


  return 0;
}
