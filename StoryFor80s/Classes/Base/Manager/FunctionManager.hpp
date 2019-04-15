//
//  FunctionManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/16/19.
//

#ifndef FunctionManager_hpp
#define FunctionManager_hpp

#include <stdio.h>
#include "BaseData.h"
using namespace std;


namespace Manager
{
  int calculateIntFromFunction(const string &calString, const BaseData *associate = nullptr);
  string getFunctionValueById(const string &functionId, const BaseData *associate = nullptr);
  BaseData* getFunctionDataById(const string &functionId);
};

#endif /* FunctionManager_hpp */
