//
//  Utils.h
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/5/19.
//

#ifndef Utils_h
#define Utils_h

#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}

#endif /* Utils_h */
