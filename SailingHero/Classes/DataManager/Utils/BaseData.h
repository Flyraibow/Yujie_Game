//
//  BaseData.h
//  SailingHero
//
//  Created by Yujie Liu on 7/15/18.
//

#ifndef BaseData_h
#define BaseData_h

#include <stdio.h>

using namespace std;

class BaseData
{
public:
  virtual string getId() const = 0;
  virtual string description() const = 0;
};

template<typename T>
set<BaseData *> fromData(set<T> realSet)
{
  set<BaseData *> baseSet;
  for (auto data : realSet) baseSet.insert(data);
  return baseSet;
}

#endif /* BaseData_h */
