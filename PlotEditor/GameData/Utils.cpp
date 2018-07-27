//
//  Utils.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 6/1/18.
//

#include "Utils.hpp"
#include <regex>

namespace SHUtil {
  
::std::string to_string(const ::std::string &str)
{
    return str;
}

::std::set<::std::string> atoset(const ::std::string &str) {
    ::std::set<::std::string> result;
    ::std::string s;
    for (int i = 0; i < str.length(); ++i) {
      char c = str.at(i);
      if (c != ' ' && c != ',' && c != '{' && c != '}') {
        s += c;
      } else if (c == ',') {
        result.insert(s);
        s = "";
      }
    }
    return result;
  }

  ::std::vector<::std::string> atovector(const ::std::string &str) {
    ::std::vector<::std::string> result;
    ::std::string s;
    for (int i = 0; i < str.length(); ++i) {
      char c = str.at(i);
      if (c != ' ' && c != ',' && c != '{' && c != '}') {
        s += c;
      } else if (c == ',') {
        result.push_back(s);
        s = "";
      }
    }
    return result;
  }
  
  
  ::std::vector<::std::pair<::std::string, ::std::string>> atomap(const ::std::string &str) {
    ::std::vector<::std::pair<::std::string, ::std::string>> result;
    ::std::string s;
    ::std::string key;
    for (int i = 0; i < str.length(); ++i) {
      char c = str.at(i);
      if (c != ' ' && c != ',' && c != '{' && c != '}' && c != ':') {
        s += c;
      } else if (c == ':') {
        key = s;
        s = "";
      } else if (c == ',') {
        result.push_back(make_pair(key, s));
        s = "";
        key = "";
      }
    }
    return result;
  }
  
#include <cstdio>
#include <cstdarg>
  
#if __cplusplus < 201703L
#include <memory>
#endif
  
  ::std::string format(const char *fmt, ...)
  {
    char buf[256];
    
    va_list args;
    va_start(args, fmt);
    const auto r = vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);
    
    if (r < 0)
      // conversion failed
      return {};
    
    const size_t len = r;
    if (len < sizeof buf)
      // we fit in the buffer
      return { buf, len };
    
#if __cplusplus >= 201703L
    // C++17: Create a ::std::string and write to its underlying array
    ::std::string s(len, '\0');
    va_start(args, fmt);
    std::vsnprintf(s.data(), len+1, fmt, args);
    va_end(args);
    
    return s;
#else
    // C++11 or C++14: We need to allocate scratch memory
    auto vbuf = ::std::unique_ptr<char[]>(new char[len+1]);
    va_start(args, fmt);
    vsnprintf(vbuf.get(), len+1, fmt, args);
    va_end(args);
    
    return { vbuf.get(), len };
#endif
  }
}

