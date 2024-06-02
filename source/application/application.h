/***

Copyright 2017 Kyle Davison

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

***/

#pragma once

#include <chrono>
#include <utility>
#include <exception>

namespace ranbam
{

typedef class time {
public:
  typedef std::chrono::high_resolution_clock clock_t;
  typedef std::chrono::time_point<clock_t> time_point_t;

  time(const time_point_t& t)
    : _timepoints{t, t - std::chrono::milliseconds(16)}
  { }

  void operator()(const time_point_t& t) {
    _timepoints[1] = _timepoints[0];
    _timepoints[0] = t;
  }

  const time_point_t current() const { return _timepoints[0]; }
  const time_point_t previous() const { return _timepoints[1]; }
  const std::chrono::nanoseconds delta() const { return std::chrono::duration_cast<std::chrono::nanoseconds>(current() - previous()); }
private:
  time_point_t _timepoints[2];
} time_t;

template<typename T>
class application {
public:
  template<typename... ARGS>
  application(ARGS&&... args)
    : _context(std::forward<ARGS>(args)...)
    , _time(time::clock_t::now())
  {
    std::to_string(time::clock_t::now().time_since_epoch().count());
  }

 int32_t run(){
    try {
      do { _time(time::clock_t::now()); } while(_context.run(_time));
    } catch(std::exception& ex) {
      return -1;
    }
    return 0;
  }

private:
  T _context;
  time _time;
};

}





int32_t Engine::Run() {
  double t = 0.0;
  double dt = 0.01
  double currenTime = hires_time_in_seconds();
  double accumulator = 0.0;

  State _previous;
  State _current;

  while(_running) {
    double newTime = time();
    double frameTime = newTime - currenttime;
    if (frameTime > 0.25)
      frametime = 0.25;
    currenttime = newTime;
    accumulator += frameTime;

    while(accumulator >= dt) {
      previousState = currentState;
      integrate(currentState, t, dt);                                    // physics->step(t, dt);
      /*
        update acceleration ( a = F/m)
        update velocity = v0 + a*dt
        update position = x0 + v*dt
        check for collisions

      */
      t += dt;
      accumulator -= dt;
    }

    double alpha = accumulator / dt;
    State state = currentState * alpha + previousState * (1.0 - alpha ); // physics->slerp( alpha );

    render(state);                                                       // renderer->render()
  }


}