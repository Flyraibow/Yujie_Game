//
//  DataManager.hpp
//  SailingHero
//
//  Created by Yujie Liu on 10/3/18.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
#include <unordered_map>
#include "BaseData.h"

using namespace std;

class DataManager
{
private:
  static DataManager* p_sharedManager;
  unordered_map<string, BaseData*> p_tempDataMap;
  unordered_map<string, string> p_tempStrMap;
public:
  static DataManager* getShareInstance();
  void setTempData(const string &key, BaseData* value);
  void setTempString(const string &key, const string &value);
  string decipherString(const string &value) const;
  BaseData* decipherData(const string &value) const;
  string getTempString(const string &key) const;
  void setDataValue(const string &key, const string &field, const string &value);
};

#endif /* DataManager_hpp */
