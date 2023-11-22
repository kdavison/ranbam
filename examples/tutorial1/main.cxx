#include <Eigen/Core>
#include <entt/entity/registry.hpp>
#include <random>
#include <iostream>

namespace _impl
{
struct null {};

template<typename T, typename TAG = _impl::null>
class Vector2 : public ::Eigen::Matrix<T,2,1> {
public:
  Vector2() : ::Eigen::Matrix<T,2,1>() {}

  Vector2(const T& x, const T& y) : ::Eigen::Matrix<T,2,1>(x,y) {}

  template<typename OTHER>
  Vector2(const ::Eigen::MatrixBase<OTHER>& other) : ::Eigen::Matrix<T,2,1>(other) {}

  template<typename OTHER>
  Vector2<T, TAG>& operator=(const ::Eigen::MatrixBase<OTHER>& other) {
    this->::Eigen::Matrix<T,2,1>::operator=(other);
    return *this;
  }
};
}


struct awake {};

template<typename T>
using Vector2 = ::_impl::Vector2<T>;

struct position_tag {};
template<typename T>
using position = ::_impl::Vector2<T, position_tag>;

struct velocity_tag {};
template<typename T>
using velocity = ::_impl::Vector2<T, velocity_tag>;

using position_t = position<double>;
using velocity_t = velocity<double>;

void print_awake(::entt::registry &registry) {
  auto view = registry.view<const position_t, const velocity_t, awake>();
  for(auto [entity, pos, vel]: view.each()) {
    std::cout << pos[0] << '.' << pos[1] << ',' << vel[0] << '.' << vel[1] << std::endl;
  }
}

int32_t main(int argc, char *argv[])
{
  entt::registry registry;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1,10);


  for(uint32_t i(0); i < 10; ++i) {
    const auto entity = registry.create();
    registry.emplace<position_t>(entity, i*1.0, i*1.0);
    registry.emplace<velocity_t>(entity, i*1.0, i*1.0);
    registry.emplace<awake>(entity);
  }

  print_awake(registry);
  std::cout << "-----" << std::endl;

  registry.each([&](auto entity){
    if (dist(gen) % 2 == 0) {
      registry.erase<awake>(entity);
    }
  });

  print_awake(registry);
  std::cout << "------" << std::endl;

  registry.each([&](auto entity){
    registry.emplace_or_replace<awake>(entity);
  });

  print_awake(registry);

  return 0;
}
