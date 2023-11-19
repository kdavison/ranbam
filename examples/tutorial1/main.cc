#include <iostream>
#include <string>
#include <cmath>
#include <numeric>


template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> idk(T x, T max, T min) {
  return x - max * std::floor(x / max);
}


int main(int argc, char *argv[])
{
  double a{0};

  std::cout << "enter some degrees: " << std::endl;

  std::cin >> a;

  std::cout << idk(a, 360.0) << std::endl;

  return 0;
}
