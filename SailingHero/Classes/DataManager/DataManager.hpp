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
  
  int getConditionIntNumber(const string &type, const string &parameter) const;
  string getConditionString(const string &type, const string &parameter) const;
public:
  static DataManager* getShareInstance();
  void setTempData(const string &key, BaseData* value);
  void setTempString(const string &key, const string &value);
  string decipherString(const string &value) const;
  BaseData* decipherData(const string &value) const;
  string getTempString(const string &key) const;
  void setData(const string &key, const string &tableName, const string &id);
  void setDataValue(const string &key, const string &field, const string &value);
  
  string getCalculationData(const string &calculationId) const;
  bool checkCondition(const string &conditionId) const;
  
  
  template <typename T, typename std::enable_if<std::is_base_of<BaseData, T>::value>::type* = nullptr>
  T* getTempData(const string &key) const {
    if (p_tempDataMap.count(key)) {
      return dynamic_cast<T*>(p_tempDataMap.at(key));
    }
    return nullptr;
  }
};

#endif /* DataManager_hpp */
