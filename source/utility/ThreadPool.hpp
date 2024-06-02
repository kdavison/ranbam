#pragma once

#include "moodycamel/blockingconcurrentqueue.h"

#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <atomic>

namespace ranbam {

class ThreadPool {
public:
  ThreadPool(const std::size_t workerCount = std::thread::hardware_concurrency(), const std::size_t waitMs = 10)
    : _running(true)
  {
    _workers.reserve(workerCount);
    for(std::size_t i = 0; i < workerCount; ++i) {
      _workers.emplace_back([this, waitMs]{
        do {
          std::function<void()> task = [](){return;};
          if (_tasks.wait_dequeue_timed(task, waitMs)) {
            task();
          }
        } while(_running);
      });
    }
  }

  ~ThreadPool() {
    _running = false;
    for(auto& worker : _workers) {
      worker.join();
    }
  }

  template<typename F, typename ... ARGS, std::enable_if_t<std::is_invocable_v<F&&, ARGS&&...>, int32_t> = 0>
  auto enqueue(F&&, ARGS&&...);

private:
  std::atomic<bool> _running;
  std::vector<std::thread> _workers;
  ::moodycamel::BlockingConcurrentQueue<std::function<void()>> _tasks;
};

template<typename F, typename ... ARGS, std::enable_if_t<std::is_invocable_v<F&&, ARGS&&...>, int32_t>>
auto ThreadPool::enqueue(F&& f, ARGS&&... args) {
  using result_t = typename std::invoke_result_t<F, ARGS ...>;

  if (!_running)
    return std::future<void>();

  auto task = std::make_shared<std::packaged_task<result_t()>>(
    std::bind(std::forward<F>(f), std::forward<ARGS>(args)...)
  );
  auto r = task->get_future();
  _tasks.enqueue([task](){
      (*task)();
  });
  return r;
}

}