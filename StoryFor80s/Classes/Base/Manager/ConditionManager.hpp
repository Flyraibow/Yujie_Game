//
//  ConditionManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/12/19.
//

#ifndef ConditionManager_hpp
#define ConditionManager_hpp

#include <stdio.h>
using namespace std;

class ConditionManager
{
private:
  static ConditionManager* p_sharedManager;
  int convertConditionStrToInt(const string &str);
public:
  static ConditionManager* getShareInstance();
  bool checkConditionByString(const string &conditionStr);
};

#endif /* ConditionManager_hpp */
