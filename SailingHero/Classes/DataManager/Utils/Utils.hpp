//
//  Utils.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 6/1/18.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <set>
#include <vector>
#include <string>
#include "BaseData.h"

namespace std {
  string to_string(const string &str);
  string to_string(const BaseData *data);
  string to_string(const set<int> &pSet);
  string to_string(const set<bool> &pSet);
  string to_string(const set<double> &pSet);
  string to_string(const set<float> &pSet);
  string to_string(const set<string> &pSet);
  string to_string(const set<long long> &pSet);
  string to_string(const set<BaseData *> &pSet);
  
  string to_string(const vector<int> &pSet);
  string to_string(const vector<bool> &pSet);
  string to_string(const vector<double> &pSet);
  string to_string(const vector<float> &pSet);
  string to_string(const vector<string> &pSet);
  string to_string(const vector<long long> &pSet);
  string to_string(const vector<BaseData *> &pSet);
  
  set<string> atoset(const string &str);
  vector<string> atovector(const string &str);
  
  string format(const char *fmt, ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;
}

#endif /* Utils_hpp */

