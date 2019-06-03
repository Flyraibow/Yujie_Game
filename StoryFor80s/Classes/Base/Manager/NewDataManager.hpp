//
//  NewDataManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 4/30/19.
//

#ifndef NewDataManager_hpp
#define NewDataManager_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "BaseData.h"

using namespace std;

/**
 * Planning to replace DataManager with this one.
 * I will do a better format with this one, so it will recognize most of the rules, and would be able to embed self defined function here
 * 1. support BaseData / int / float / string / bool
 *
 *
 */
class NewDataManager
{
private:
  static NewDataManager* p_sharedManager;
  string decipherNoParenthesisString(const string &str, const BaseData *associateData = nullptr) const;
  string decipherParenthesis(const string &str, const BaseData *associateData = nullptr) const;
public:
  BaseData* decipherData(const string &str, const BaseData *associateData = nullptr) const;
  vector<BaseData*> decipherDataList(const string &str, const BaseData *associateData = nullptr) const;
  string decipherString(const string &str, const BaseData *associateData = nullptr) const;
  bool decipherCondition(const string &str, const BaseData *associateData = nullptr) const;
};

#endif /* NewDataManager_hpp */
