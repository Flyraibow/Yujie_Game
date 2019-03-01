//
//  DataManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#include "DataManager.hpp"

#include "ConditionData.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"
#include "ConditionCalculationData.hpp"
#include "FunctionCalculationData.hpp"
#include "GameData.hpp"
#include "BaseDataManager.hpp"
#include "FunctionManager.hpp"
#include "BaseGlobalDataManager.hpp"


DataManager* DataManager::p_sharedManager = nullptr;

DataManager* DataManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new DataManager();
  }
  return p_sharedManager;
}


void DataManager::setTempData(const string &key, BaseData* value)
{
  p_tempDataMap[key] = value;
}

void DataManager::setTempDataList(const string &key, const vector<BaseData*> &value)
{
  p_tempDataListMap[key] = value;
}

string DataManager::getTempString(const string &key) const
{
  if (p_tempStrMap.count(key)) {
    return p_tempStrMap.at(key);
  }
  return "";
}

void DataManager::setTempString(const string &key, const string &value)
{
  p_tempStrMap[key] = decipherString(value);
}

void DataManager::calculateTempString(const string &type, const string &key, const string &func, const string &value)
{
  auto result = calculate(type, p_tempStrMap.at(key), decipherString(value), func);
  setTempString(key, result);
}

void DataManager::setData(const string &key, const string &tableName, const string &id)
{
  auto strId = decipherString(id);
  auto data = BaseDataManager::getData(tableName, strId);
  if (data != nullptr) {
    setTempData(key, data);
  } else {
    data = BaseGlobalDataManager::getData(tableName, strId);
    if (data != nullptr) {
      setTempData(key, data);
    } else {
      CCLOGWARN("Couldn't find data from key : %s", key.c_str());
    }
  }
}

void DataManager::setDataList(const string &key, const string &tableName, const string &id)
{
  vector<BaseData *> dataList;
  auto strIdList = Utils::atovector(decipherString(id));
  for (auto strId : strIdList) {
    auto data = BaseDataManager::getData(tableName, strId);
    if (data != nullptr) {
      dataList.push_back(data);
    } else {
      data = BaseGlobalDataManager::getData(tableName, strId);
      if (data != nullptr) {
        dataList.push_back(data);
      } else {
        CCLOGWARN("Couldn't find data from key : %s", key.c_str());
      }
    }
  }
  setTempDataList(key, dataList);
}

void DataManager::setDataList(const string &key, const string &tableName, const string &tempListKey, const string &id)
{
  vector<BaseData *> dataList;
  if (p_tempDataListMap.count(tempListKey)) {
    auto tempList = p_tempDataListMap.at(tempListKey);
    for (auto tempData : tempList) {
      auto strId = tempData->getFieldValue(id);
      auto data = BaseDataManager::getData(tableName, strId);
      if (data != nullptr) {
        dataList.push_back(data);
      } else {
        data = BaseGlobalDataManager::getData(tableName, strId);
        if (data != nullptr) {
          dataList.push_back(data);
        }
      }
    }
  } else {
    CCLOGWARN("Couldn't find list from key : %s", tempListKey.c_str());
  }
  
  setTempDataList(key, dataList);
}

void DataManager::filtDataList(const string &key, const string &tempKey, const string &conditionId)
{
  vector<BaseData *> dataList;
  if (p_tempDataListMap.count(key)) {
    auto tempList = p_tempDataListMap.at(key);
    for (auto tempData : tempList) {
      setTempData(tempKey, tempData);
      if (checkCondition(conditionId)) {
        dataList.push_back(tempData);
      }
    }
  } else {
    CCLOGWARN("Couldn't find list from key : %s", key.c_str());
  }
  setTempDataList(key, dataList);
}

void DataManager::setDataValue(const string &key, const string &field, const string &value)
{
  auto data = decipherData(key);
  if (data != nullptr) {
    data->setFieldValue(field, decipherString(value));
  } else {
    CCLOGWARN("Couldn't find data from key : %s", key.c_str());
  }
}

void DataManager::setDataValue(const string &key, const string &field, const string &type, const string &func, const string &value)
{
  auto data = decipherData(key);
  auto funcValue = decipherString(value);
  if (data != nullptr) {
    auto result = calculate(type, data->getFieldValue(field), funcValue, func);
    data->setFieldValue(field, result);
  } else {
    CCLOGWARN("Couldn't find data from key : %s", key.c_str());
  }
}

void DataManager::setValue(const string &key, const string &value)
{
  auto keyList = Utils::split(key, '.');
  CCASSERT(keyList.size() >= 2, "The size of key list should be >= 2");
  auto keyType = keyList.at(0);
  if (keyType == "game") {
    setDataValue(keyType, keyList.at(1), value);
  } else if (keyType == "data") {
    CCASSERT(keyList.size() >= 3, "The size of data-key list should be >= 3");
    setDataValue(keyType + '.' + keyList.at(1), keyList.at(2), value);
  } else if (keyType == "temp") {
    setTempString(keyList.at(1), value);
  } else {
    CCLOGERROR("Un-recognized key : %s", key.c_str());
  }
}

void DataManager::setSortKeyValuePair(const string &key, const string &type, const string &content, const string &orderConditionId)
{
  vector<pair<string, string>> result;
  auto strContent = decipherString(content);
  typedef function<bool(pair<string, string>, pair<string, string>)>  Comparator;
  Comparator compFunctor =
  [this, orderConditionId](std::pair<std::string, string> elem1 ,std::pair<std::string, string> elem2)
  {
    this->setTempString("leftKey", elem1.first);
    this->setTempString("rightKey", elem2.first);
    this->setTempString("leftValue", elem1.second);
    this->setTempString("rightValue", elem2.second);
    return this->checkCondition(orderConditionId);
  };
  if (type == "map") {
    auto mapContent = Utils::atomap(strContent);
    set<pair<string, string>, Comparator> setOfPairs(mapContent.begin(), mapContent.end(), compFunctor);
    for (pair<string, string> element : setOfPairs) {
      result.push_back(element);
    }
  } else {
    CCLOGERROR("unsopport type: %s", type.c_str());
  }
  p_tempKeyValueMap[key] = result;
}

BaseData* DataManager::decipherData(const string &value) const
{
  auto args = Utils::split(value, '.');
  if (value == "game") {
    return GameData::getSharedInstance();
  } else if (args.size() > 1) {
    auto k = args.at(0);
    auto v = args.at(1);
    if (k == "data") {
      if (p_tempDataMap.count(v)) {
        return p_tempDataMap.at(v);
      }
    }
  }
  return nullptr;
}

vector<BaseData*> DataManager::decipherDataList(const string &value) const
{
  vector<BaseData*> result;
  auto args = Utils::split(value, '.');
  if (args.size() == 1) {
    if (p_tempDataListMap.count(value)) {
      result = p_tempDataListMap.at(value);
    }
  } else {
    CCLOGERROR("not define data list value: %s", value.c_str());
  }
  
  return result;
}

string DataManager::decipherString(const string &value) const
{
  auto args = Utils::split(value, '.');
  string val = value;
  if (args.size() > 1) {
    auto k = args.at(0);
    if (k == "translation") {
      val = LocalizationHelper::getLocalization(args.at(1));
    } else if (k == "temp") {
      auto dataKey = args.at(1);
      if (p_tempStrMap.count(dataKey)) {
        val = p_tempStrMap.at(dataKey);
      } else {
        CCLOGWARN("Temp string doesn't contain this value : %s", dataKey.c_str());
      }
    } else if (k == "game") {
      val = GameData::getSharedInstance()->getFieldValue(args.at(1));
    } else if (k == "gamedata") {
      if (args.size() == 4) {
        val = BaseDataManager::getDataField(args.at(1), args.at(2), args.at(3));
      } else {
        CCLOGWARN("gamedata string doesn't contain this value : %s", value.c_str());
      }
    } else if (k == "globaldata") {
      if (args.size() == 4) {
        val = BaseGlobalDataManager::getDataField(args.at(1), args.at(2), args.at(3));
      } else {
        CCLOGWARN("globaldata string doesn't contain this value : %s", value.c_str());
      }
    } else if (k == "data") {
      auto dataKey = args.at(1);
      if (p_tempDataMap.count(dataKey)) {
        if (args.size() > 2) {
          val = p_tempDataMap.at(dataKey)->getFieldValue(args.at(2));
        } else {
          val = p_tempDataMap.at(dataKey)->description();
          CCLOGWARN("Cannot decipher value : %s", value.c_str());
        }
      } else {
        CCLOGWARN("Cannot decipher value : %s", value.c_str());
      }
    } else if (k == "function") {
      auto functionId = args.at(1);
      if (args.size() == 2) {
        val = Manager::getFunctionValueById(functionId);
      } else if (args.size() == 3) {
        auto data = Manager::getFunctionDataById(functionId);
        val = data->getFieldValue(args.at(2));
      } else {
        CCLOGWARN("Cannot decipher value : %s", value.c_str());
      }
    } else if (k == "calculation") {
      auto calculationId = args.at(1);
      if (args.size() == 2) {
        val = getCalculationData(calculationId);
      } else {
        CCLOGWARN("Cannot decipher value : %s", value.c_str());
      }
    } else if (k == "list") {
      auto key = args.at(1);
      if (p_tempDataListMap.count(key) && args.size() >= 4) {
        auto list = p_tempDataListMap.at(key);
        auto index = atoi(args.at(2).c_str());
        if (list.size() > index) {
          val = list.at(index)->getFieldValue(args.at(3));
        } else {
          val = args.size() > 4 ? args.at(4) : "";
        }
      } else {
        CCLOGWARN("Cannot decipher value : %s", value.c_str());
      }
    } else if (k == "map") {
      auto key = args.at(1);
      if (p_tempKeyValueMap.count(key) && args.size() > 2) {
        auto list = p_tempKeyValueMap.at(key);
        if (args.size() == 3) {
          auto n = args.at(2);
          vector<string> res;
          for (auto p : list) {
            if (n == "keyList") {
              res.push_back(p.first);
            } else if (n == "valueList") {
              res.push_back(p.second);
            }
          }
          val = Utils::to_string(res);
        } else if (args.size() >= 4) {
          auto index = atoi(args.at(2).c_str());
          if (index < list.size()) {
            auto p = list.at(index);
            auto n = args.at(3);
            if (n == "key") {
              val = p.first;
            } else if (n == "value") {
              val = p.second;
            }
          } else {
            val = args.size() > 4 ? args.at(4) : "";
          }
        }
      }
    }
  }
  return val;
}

string DataManager::getCalculationData(const string &calculationId) const
{
  auto calculationData = ConditionCalculationData::getConditionCalculationDataById(calculationId);
  CCASSERT(calculationData != nullptr, ("calculation data is null:" + calculationId).c_str());
  auto flag = checkCondition(calculationData->getConditionId());
  if (flag) {
    return getConditionString(calculationData->getYesType(), calculationData->getYesParameter());
  } else {
    return getConditionString(calculationData->getNoType(), calculationData->getNoParameter());
  }
}

#include <unordered_set>

string DataManager::getConditionString(const string &type, const string &parameter) const
{
  if (type == "calculation") {
    return getCalculationData(parameter);
  } else if (type == "int" || type == "string" ) {
    return parameter;
  }
  CCASSERT(false, ("Doesn't allow this type: " + type).c_str());
}

int DataManager::getConditionIntNumber(const string &type, const string &parameter) const
{
  if (type == "int") {
    auto str = decipherString(parameter);
    return atoi(str.c_str());
  } else if (type == "calculation") {
    auto str = getCalculationData(parameter);
    return atoi(str.c_str());
  }
  CCASSERT(false, "Doesn't allow this type");
}

//bool compareInteger(int leftValue, int rightValue, const string &compare)
//{
//  if (compare == "<") {
//    return leftValue < rightValue;
//  } else if (compare == "<=") {
//    return leftValue <= rightValue;
//  } else if (compare == ">") {
//    return leftValue > rightValue;
//  } else if (compare == ">=") {
//    return leftValue >= rightValue;
//  } else if (compare == "=") {
//    return leftValue == rightValue;
//  } else if (compare == "!=") {
//    return leftValue != rightValue;
//  }
//  CCASSERT(false, "unrecognize compare type");
//}

bool logicCondition(const string &leftCondition, const string &rightCondition, const string &logic) {
  auto instance = DataManager::getShareInstance();
  if (logic == "and") {
    return instance->checkCondition(leftCondition) && instance->checkCondition(rightCondition);
  } else if (logic == "or") {
    return instance->checkCondition(leftCondition) || instance->checkCondition(rightCondition);
  } else if (logic == "xor") {
    return instance->checkCondition(leftCondition) ^ instance->checkCondition(rightCondition);
  }
  CCASSERT(false, "unrecognize logic type");
}

bool DataManager::checkCondition(const string &conditionId) const
{
//  auto conditionData = ConditionData::getConditionDataById(conditionId);
//  auto compareType = conditionData->getCompareFunction();
//  static const unordered_set<string> comparison = {"<", ">", "=", "<=", ">=", "!="};
//  static const unordered_set<string> logic = {"and", "or", "xor"};
//  if (comparison.count(compareType)) {
//    // compare the number
//    // TODO currently only int value can compare
//    auto leftValue = getConditionIntNumber(conditionData->getLeftType(), conditionData->getLeftParameter());
//    auto rightValue = getConditionIntNumber(conditionData->getRightType(), conditionData->getRightParameter());
//    return compareInteger(leftValue, rightValue, compareType);
//  } else if (logic.count(compareType)) {
//    return logicCondition(conditionData->getLeftParameter(), conditionData->getRightParameter(), compareType);
//  } else if (compareType == "belong") {
//    auto str = getConditionString(conditionData->getLeftType(), conditionData->getLeftParameter());
//    auto strList = Utils::split(conditionData->getRightParameter(), ';');
//    unordered_set<string> container;
//    for (auto s : strList) {
//      container.insert(decipherString(s));
//    }
//    return container.count(str);
//  }
  return true;
}



string DataManager::calculate(const string &type, const string &a, const string &b, const string &func)
{
  if (type == "int") {
    int origin = atoi(a.c_str());
    int funcValue = atoi(b.c_str());
    int result = 0;
    if (func == "-") {
      result = origin - funcValue;
    } else if (func == "+") {
      result = origin + funcValue;
    } else {
      CCLOGERROR("CALCULATION FUNCTION NOT DEFINED : %s", func.c_str());
    }
    return to_string(result);
  } else {
    CCLOGERROR("CALCULATION TYPE NOT DEFINED : %s", type.c_str());
  }
  return "";
}

string DataManager::formatStringWithParamters(const string &str, const vector<string> &parameters) const
{
  string result = str;
  vector<string> decipheredParams;
  for (auto parameter : parameters) {
    decipheredParams.push_back(decipherString(parameter));
  }
  switch (decipheredParams.size()) {
    case 1: {
      result = Utils::format(str.c_str(), decipheredParams.at(0).c_str());
      break;
    }
    case 2: {
      result = Utils::format(str.c_str(), decipheredParams.at(0).c_str(), decipheredParams.at(1).c_str());
      break;
    }
    case 3: {
      result = Utils::format(str.c_str(), decipheredParams.at(0).c_str(), decipheredParams.at(1).c_str(), decipheredParams.at(2).c_str());
      break;
    }
    case 4: {
      result = Utils::format(str.c_str(), decipheredParams.at(0).c_str(), decipheredParams.at(1).c_str(), decipheredParams.at(2).c_str(), decipheredParams.at(3).c_str());
      break;
    }
    default:
      break;
  }
  return result;
}
