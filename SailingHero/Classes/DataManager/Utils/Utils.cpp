//
//  Utils.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 6/1/18.
//

#include "Utils.hpp"

using namespace std;

namespace std {
  string to_string(const string &str) {
    return str;
  }
  template<typename T>
  string to_string(const unordered_set<T> &pSet) {
    string st = "{ ";
    for (auto str : pSet) {
      st += to_string(str) + ", ";
    }
    st += "}";
    return st;
  }
  
  template<typename T>
  string to_string(const vector<T> &pSet) {
    string st = "{ ";
    for (auto str : pSet) {
      st += to_string(str) + ", ";
    }
    st += "}";
    return st;
  }
  
  string to_string(const unordered_set<string> &pSet) {
    return to_string<string>(pSet);
  }
  
  string to_string(const unordered_set<int> &pSet) {
    return to_string<int>(pSet);
  }
  
  string to_string(const unordered_set<bool> &pSet) {
    return to_string<bool>(pSet);
  }
  string to_string(const unordered_set<double> &pSet){
    return to_string<double>(pSet);
  }
  
  string to_string(const unordered_set<float> &pSet) {
    return to_string<float>(pSet);
  }
  
  string to_string(const unordered_set<long long> &pSet) {
    return to_string<long long>(pSet);
  }
  
  string to_string(const vector<int> &pSet) {
    return to_string<int>(pSet);
  }
  
  string to_string(const vector<bool> &pSet) {
    return to_string<bool>(pSet);
  }
  
  string to_string(const vector<double> &pSet) {
    return to_string<double>(pSet);
  }
  
  string to_string(const vector<float> &pSet) {
    return to_string<float>(pSet);
  }
  
  string to_string(const vector<string> &pSet) {
    return to_string<string>(pSet);
  }
  
  string to_string(const vector<long long> &pSet) {
    return to_string<long long>(pSet);
  }
  
#include <cstdio>
#include <cstdarg>
  
#if __cplusplus < 201703L
#include <memory>
#endif
  
  string format(const char *fmt, ...)
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
    // C++17: Create a string and write to its underlying array
    std::string s(len, '\0');
    va_start(args, fmt);
    std::vsnprintf(s.data(), len+1, fmt, args);
    va_end(args);
    
    return s;
#else
    // C++11 or C++14: We need to allocate scratch memory
    auto vbuf = unique_ptr<char[]>(new char[len+1]);
    va_start(args, fmt);
    vsnprintf(vbuf.get(), len+1, fmt, args);
    va_end(args);
    
    return { vbuf.get(), len };
#endif
  }
}

