#include "string.hpp"
#include <string_view>
#include <algorithm>

namespace ranbam
{
namespace string
{
/*
This is BY FAR the safer version...so if speed isn't a critical issue use this.
see the comment on the other version
*/
template<>
std::vector<std::string> tokenize(const std::string& input, const char& token) {
  std::vector<std::string> result;
  std::size_t p1,p2;
  for(p1 = 0, p2 = 0; p2 != std::string::npos;) {
    p2 = a.find(token, p1);
    result.emplace_back(a.substr(p1, std::min(input.size()-p1, p2-p1)));
    p1 = p2+1;
  }
  return result;
}

/*
This is 30% faster then the std::string version
but one has to be extremely careful that the source string 'input' exists for
the entire lifetime of the result 'std::vector<std::string_view>', else you
got a memory leak and probably a SEGFAULT ticking timebomb
*/
template<>
std::vector<std::string_view> tokenize(const std::string& a, const char& token) {
  std::vector<std::string_view> result;
  std::size_t p1,p2;
  for(p1 = 0, p2 = 0; p2 != std::string::npos;) {
    p2 = a.find(token, p1);
    result.emplace_back(std::string_view(a.data()+p1, std::min(a.size()-p1, p2-p1)));
    p1 = p2+1;
  }
  return result;
}

namespace _impl
{
template<typename T>  
bool globish_match(const std::vector<T>& lhs, const std::vector<T>& rhs) const {
  bool match(false);
  if(lhs.front() == "**") return true;
  if(lhs.back() == "**" || lhs.size() == rhs.size()) {
    const decltype(lhs.size()) mod = lhs.back() == "**" ? -1 : 0;
    for(auto i(0); i < std::min(lhs.size(), rhs.size())+mod; ++i) {
      match = lhs.at(i) == "*" ? true : lhs.at(i) == rhs.at(i);
    }
  }
  return match;
}
}
}
}

