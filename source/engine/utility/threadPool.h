#pragma once

#include <memory>
#include <mutex>
#include <cstdint>

namespace UTILITY
{

class ThreadPool {
public:
  ThreadPool(const std::size_t size)
    : _running(true)
  {
    for(std::size_t count(size); count > 0; --count) {
      _threads.emplace_back([this]{
        std::function<void()> task;
        do {
          {
            std::unique_lock<decltype(this->_TaskMutex)> lock(this->_TaskMutex);
            if(this->_tasks.empty()) {
              this->_TaskCV.wait(lock, [this]{ return !this->_running || !this->_tasks.empty(); });
            }
            if(!this->_running && this->_tasks.empty()) { return; }
            task = std::move(this->_tasks.front());
            this->_tasks.pop();
          }
          task();
        } while(this->_running);
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<decltype(_TaskMutex)> lock(_TaskMutex);
      _running = false;
    }
    _TaskCV.notify_all();
    for(auto& thread : _threads) {
      thread.join();
    }
  }

  template<typename F, typename... ARGS>
  auto enqueue(F&& f, ARGS&&... args) -> std::future<std::result_of_t<F(ARGS...)>> {
    using result_t = std::result_of_t<F(ARGS...)>;
    auto task = std::make_shared<std::packaged_task<result_t()>>(
      std::bind(std::forward<F>(f), std::forward<ARGS>(args)...)
    );
    auto r = task->get_future();

    {
      std::unique_lock<decltype(_TaskMutex)> lock(_TaskMutex);
      if(!_running) throw std::runtime_error("threadpool stopped");
      _tasks.emplace([task]{(*task)();});
    }

    _TaskCV.notify_one();
    return r;
  }

private:
  std::vector<std::thread> _threads;
  std::mutex _TaskMutex;
  std::condition_variable _TaskCV;
  std::queue<std::function<void()>> _tasks;
  std::atomic<bool> _running;
};
}  //::UTILITY
