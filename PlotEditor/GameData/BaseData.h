//
//  BaseData.h
//  SailingHero
//
//  Created by Yujie Liu on 7/15/18.
//

#ifndef BaseData_h
#define BaseData_h

#include <set>
#include <cstdio>

#include "cocos2d.h"

using std::string;
template <class T>
using vector = std::vector<T>;
template <class T>
using set = std::set<T>;
template <class K, class T>
using map = std::map<K, T>;
template <class T1, class T2>
using pair = std::pair<T1, T2>;

class BaseData
{
public:
  virtual std::string getId() const = 0;
  virtual std::string description() const = 0;
};

template<typename T>
std::set<BaseData *> fromData(std::set<T> realSet)
{
  std::set<BaseData *> baseSet;
  for (auto data : realSet) baseSet.insert(data);
  return baseSet;
}

#endif /* BaseData_h */
