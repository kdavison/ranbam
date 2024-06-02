#pragma once

#include <vector>
#include <string>

namespace ranbam
{
namespace string
{
/*
default this template to std::string 
to try and help/force users to use the correct version 
*/
template<typename T=std::string>
std::vector<T> tokenize(const std::string& input, const char& token);




namespace _impl
{
template<typename T=std::string>
bool globish_match(const std::vector<T>& lhs, const std::vector<T>& rhs);
}
/*
not a good place for this to live...maybe just in the messenging system?
rules:
1. token delimited string such as 'a:b:c:d'
2. '*' wildcard matches any 1 depth. 'a:*:b' matches 'a:z:b' AND 'a:b:b'
3. '**' must be the end of the glob and matches any depth 'a:**' matches 'a:b:c' and 'a:z'
*/

template<typename T=std::string>
bool globish(const std::string& lhs, const std::string& rhs, const char& delimiter) {
  return _impl::globish_match<T>(tokenize<T>(lhs, delimiter), tokenize<T>(rhs, delimiter));
}


}
}