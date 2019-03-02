//
//  Utils.cpp
//
//  Created by Yujie Liu on 6/1/18.
//

#include "Utils.hpp"
#include <sstream>
#include <regex>

using namespace std;

namespace Utils {
  
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

  ::std::vector<::std::string> split(const ::std::string &s, char delim) {
    ::std::stringstream ss(s);
    ::std::string item;
    ::std::vector<::std::string> tokens;
    while (getline(ss, item, delim)) {
      tokens.push_back(item);
    }
    return tokens;
  }
  
  ::std::string join(const ::std::vector<::std::string> &v, const string &jointer) {
    std::stringstream ss;
    for(size_t i = 0; i < v.size(); ++i)
    {
      if(i != 0)
        ss << jointer;
      ss << v[i];
    }
    return ss.str();
  }
  
  int utf8_strlen(const ::std::string& str)
  {
    int c,i,ix,q;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
      c = (unsigned char) str[i];
      if      (c>=0   && c<=127) i+=0;
      else if ((c & 0xE0) == 0xC0) i+=1;
      else if ((c & 0xF0) == 0xE0) i+=2;
      else if ((c & 0xF8) == 0xF0) i+=3;
      //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
      //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
      else return 0;//invalid utf8
    }
    return q;
  }
  
  ::std::string utf8_substr(const ::std::string& str, int start, int len)
  {
    int q = 0;
    int i;
    ::std::string result;
    for (i = 0; q < start; ++i, ++q) {
      char c = (unsigned char) str[i];
      if      (c>=0   && c<=127) i+=0;
      else if ((c & 0xE0) == 0xC0) i+=1;
      else if ((c & 0xF0) == 0xE0) i+=2;
      else if ((c & 0xF8) == 0xF0) i+=3;
      else return "";//invalid utf8
    }
    int j = i;
    for (; q < len && j < str.length(); ++j, ++q) {
      char c = (unsigned char) str[j];
      if      (c>=0   && c<=127) j+=0;
      else if ((c & 0xE0) == 0xC0) j+=1;
      else if ((c & 0xF0) == 0xE0) j+=2;
      else if ((c & 0xF8) == 0xF0) j+=3;
      else return "";//invalid utf8
    }
    return str.substr(i, j - i);
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

