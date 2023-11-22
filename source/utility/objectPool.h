#pragma once

#include <memory>

namespace UTILITY
{
namespace UTILITY
{
namespace impl
{
template<typename T, typename D>
class ObjectPool final
  : public std::enable_shared_from_this<ObjectPool<T,D>>
{
public:
  auto acquire() -> std::unique_ptr<T, std::function<void(T*)>>;
  void add(std::unique_ptr<T,D> t);
  const bool empty() const;
  const std::size_t size() const;
private:
  std::stack<std::unique_ptr<T,D>> _pool;
};

template<typename T, typename D>
class LockedObjectPool : public ObjectPool<T,D>
{
public:
  auto acquire() -> std::unique_ptr<T, std::function<void(T*)>>;
  void add(std::unique_ptr<T,D> t);
  const bool empty();
  const std::size_t size();
private:
  std::mutex _mutex;
};
}  //::UTILITY::impl

template<typename T, typename D = std::default_delete<T>>
using ObjectPool = std::shared_ptr<impl::ObjectPool<T,D>>;

template<typename T, typename D = std::default_delete<T>>
using LockedObjectPool = std::shared_ptr<impl::LockedObjectPool<T,D>>;

}  //::UTILITY
