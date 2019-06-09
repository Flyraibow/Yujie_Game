//
//  ConditionManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/12/19.
//

#ifndef ConditionManager_hpp
#define ConditionManager_hpp

#include <stdio.h>

class BaseData;

using namespace std;

namespace Manager
{
  bool checkConditionByString(const string &conditionStr, BaseData* associate = nullptr);
};

#endif /* ConditionManager_hpp */
