#include "engine/engine.hpp"

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