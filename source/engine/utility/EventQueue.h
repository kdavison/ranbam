#pragma once

#include <typeinfo>
#include <typeindex>
#include "moodycamel/concurrentqueue.h"
#include "utility/compile_time_id.h"

namespace ranbam {
class iEvent {
public:
  typedef uint64_t type_t;
  typedef uint64_t id_t;
public:
  virtual ~iEvent() = default;
  virtual type_t type() const = 0;
  virtual id_t source() const = 0;
  virtual id_t destination() const = 0;
};

template<typename T>
class Event
  : public iEvent
{
public:
  template<typename... ARGS>
  Event(const id_t s, const id_t d, ARGS&&... args)
    : _source(s)
    , _destination(d)
    , _payload(std::forward<ARGS>(args)...)
  {
  }

  static const type_t TYPE;
  type_t type() const final override { return TYPE; }
  id_t source() const { return _source; }
  id_t destination() const { return _destination; }
  T payload() const { return _payload; }

private:
  const iEvent::id_t _source;
  const iEvent::id_t _destination;
  T _payload;
};

template<typename T>
const iEvent::type_t Event<T>::TYPE = ::compile::identifier<Event<T>>::ID();

class iEventQueue {
public:
  virtual ~iEventQueue() = default;
  virtual void enqueue(std::shared_ptr<iEvent>&& e) = 0;
  virtual std::shared_ptr<iEvent> dequeue() = 0;
  virtual std::size_t size() const = 0;
};

class EventQueue
  : public iEventQueue
{
public:
  void enqueue(std::shared_ptr<iEvent>&& e) final override {
    _queue.enqueue(e);
  }

  std::shared_ptr<iEvent> dequeue() final override {
    std::shared_ptr<iEvent> e(nullptr);
    _queue.try_dequeue(e);
    return std::move(e);
  }

  std::size_t size() const final override { return _queue.size_approx(); }
private:
  ::moodycamel::ConcurrentQueue<std::shared_ptr<iEvent>> _queue;
};
}
