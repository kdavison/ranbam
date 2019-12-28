#include "utility/compile_time_id.h"
#include <iostream>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <functional>
#include <unordered_set>

//event bus stuff
// 1. queue
// 2. observer interface
// 3. system->run()

template<typename T>
class obserable {
public:
  typedef std::unordered_set<std::shared_ptr<T>> observers_t;

  void connect(std::shared_ptr<T> const& spObserver) {
    _observers.emplace(spObserver);
  }

  void disconnect(std::shared_ptr<T> const& spObserver) {
    
  }

  template<typename N>
  void dispatch(N const& notification) {
    for(auto const& spObserver : _observers) {
      spObserver->dispatch(notification);
    }
  }

private:
  observers_t _observers;
};

int main(int argc, char *argv[])
{

  return 0;
}
