//
//  DataManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "BaseData.h"

class FunctionCalculationData;

using namespace std;

class DataManager
{
private:
  static DataManager* p_sharedManager;
  unordered_map<string, BaseData*> p_tempDataMap;
  unordered_map<string, vector<BaseData*>> p_tempDataListMap;
  unordered_map<string, string> p_tempStrMap;
  unordered_map<string, vector<pair<string, string>>> p_tempKeyValueMap;
  
  int getConditionIntNumber(const string &type, const string &parameter) const;
  string getConditionString(const string &type, const string &parameter) const;
  string getFormatStringFromFunction(FunctionCalculationData *functionData) const;
  string calculate(const string &type, const string &a, const string &b, const string &func);
public:
  static DataManager* getShareInstance();
  void setTempData(const string &key, BaseData* value);
  void setTempDataList(const string &key, const vector<BaseData*> &value);
  void setTempString(const string &key, const string &value);
  void calculateTempString(const string &type, const string &key, const string &func, const string &value);
  string decipherString(const string &value) const;
  BaseData* decipherData(const string &value) const;
  vector<BaseData*> decipherDataList(const string &value) const;
  string getTempString(const string &key) const;
  void setData(const string &key, const string &tableName, const string &id);
  void setDataList(const string &key, const string &tableName, const string &id);
  void setDataList(const string &key, const string &tableName, const string &tempListKey, const string &id);
  void filtDataList(const string &key, const string &tempKey, const string &conditionId);
  void setDataValue(const string &key, const string &field, const string &value);
  void setDataValue(const string &key, const string &field, const string &type, const string &func, const string &value);
  void setSortKeyValuePair(const string &key, const string &type, const string &content, const string &orderConditionId);
  void setValue(const string &key, const string &value);
  
  string getCalculationData(const string &calculationId) const;
  BaseData* getFunctionData(const std::string &functionId) const;
  bool checkCondition(const string &conditionId) const;
  
  template <typename T, typename std::enable_if<std::is_base_of<BaseData, T>::value>::type* = nullptr>
  T* getTempData(const string &key) const {
    if (p_tempDataMap.count(key)) {
      return dynamic_cast<T*>(p_tempDataMap.at(key));
    }
    return nullptr;
  }
  
  template <typename T, typename std::enable_if<std::is_base_of<BaseData, T>::value>::type* = nullptr>
  T* decipherData(const string &value) const {
    auto data = decipherData(value);
    if (data != nullptr) {
      return dynamic_cast<T*>(data);
    }
    return nullptr;
  }
};

#endif /* DataManager_hpp */
