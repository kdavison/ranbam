#include "objectPool.h"
#include <functional>
#include <stack>
#include <mutex>
#include <cstdint>

namespace UTILITY
{
namespace impl
{
template<typename T, typename D>
class ObjectPool final
  : public std::enable_shared_from_this<ObjectPool<T,D>>
{
public:
  auto acquire() {
    if(empty()) { throw std::out_of_range("ObjectPool is empty"); }

    std::weak_ptr<ObjectPool<T,D>> wkPool = this->shared_from_this();
    auto fnDelete = [wkPool](T* pointer)->void{
      if(auto spPool = wkPool.lock()) {
        spPool->add(std::unique_ptr<T,D>(pointer));
      } else {
        D{}(pointer);
      }
    };

    {
      auto object = std::unique_ptr<T, decltype(fnDelete)>(
        _pool.top().release(),
        fnDelete
      );
      _pool.pop();
      return std::move(object);
    }
  }

  void add(std::unique_ptr<T,D> t) {
    _pool.push(std::move(t));
  }

  const bool empty() const {
    return _pool.empty();
  }

  const std::size_t size() const {
    return _pool.size();
  }

private:
  std::stack<std::unique_ptr<T,D>> _pool;
};

template<typename T, typename D>
class LockedObjectPool : public ObjectPool<T,D>
{
public:
  auto acquire() {
    std::lock_guard<decltype(_mutex)> lock(_mutex);
    return ObjectPool<T,D>::acquire();
  }

  void add(std::unique_ptr<T,D> t) {
    std::lock_guard<decltype(_mutex)> lock(_mutex);
    ObjectPool<T,D>::add(std::move(t));
  }

  const bool empty() {
    std::lock_guard<decltype(_mutex)> lock(_mutex);
    return ObjectPool<T,D>::empty();
  }

  const std::size_t size() {
    std::lock_guard<decltype(_mutex)> lock(_mutex);
    return ObjectPool<T,D>::size();
  }

private:
  std::mutex _mutex;
};
}  //::UTILITY::impl
}  //::UTILITY
