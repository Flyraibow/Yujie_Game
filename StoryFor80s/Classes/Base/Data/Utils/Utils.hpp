//
//  Utils.hpp
//
//  Created by Yujie Liu on 6/1/18.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <set>
#include <vector>
#include <string>
#include <map>
#include "BaseData.h"


namespace Utils {
  
  template<typename T>
  ::std::string to_string(T value) {
    return ::std::to_string(value);
  }
  
  ::std::string to_string(const ::std::string &str);
  
  ::std::string to_lower_string(const ::std::string &str);
  
  template<typename T>
  ::std::string to_string(const ::std::set<T> &pSet) {
    ::std::string st = "{ ";
    for (auto str : pSet) {
      st += to_string(str) + ", ";
    }
    st += "}";
    return st;
  }
  
  template<typename T>
  ::std::string to_string(const ::std::vector<T> &pSet) {
    ::std::string st = "{ ";
    for (auto str : pSet) {
      st += to_string(str) + ", ";
    }
    st += "}";
    return st;
  }
  
  template<typename T, typename P>
  ::std::string to_string(const ::std::map<T, P> &pMap) {
    ::std::string st = "{ ";
    for (auto iter = pMap.begin(); iter != pMap.end(); ++iter) {
      st += to_string(iter->first) + ":" + to_string(iter->second) + ",";
    }
    st += "}";
    return st;
  }

  ::std::set<::std::string> atoset(const ::std::string &str);
  ::std::vector<::std::string> atovector(const ::std::string &str);
  ::std::vector<::std::pair<::std::string, ::std::string>> atomap(const ::std::string &str);
  ::std::vector<::std::string> split(const ::std::string &s, char delim);
  ::std::string join(const ::std::vector<::std::string> &v, const string &jointer);
  
  int utf8_strlen(const ::std::string& str);
  ::std::string utf8_substr(const ::std::string& str, int start, int len);
  
  ::std::string format(const char *fmt, ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;
}

#endif /* Utils_hpp */

