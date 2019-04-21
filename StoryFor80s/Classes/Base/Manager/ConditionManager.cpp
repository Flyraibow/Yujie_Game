//
//  ConditionManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/12/19.
//

#include "ConditionManager.hpp"

#include "DataManager.hpp"
#include "Utils.hpp"

string findCompareType(const string &conditionStr)
{
  if (conditionStr.find(";") != string::npos) {
    return ";";
  } else if (conditionStr.find("<=") != string::npos) {
    return "<=";
  } else if (conditionStr.find(">=") != string::npos) {
    return ">=";
  } else if (conditionStr.find("!=") != string::npos) {
    return "!=";
  } else if (conditionStr.find(">") != string::npos) {
    return ">";
  } else if (conditionStr.find("<") != string::npos) {
    return "<";
  } else if (conditionStr.find("=") != string::npos) {
    return "=";
  }
  return "";
}

bool compareInteger(int leftValue, int rightValue, const string &compare)
{
  if (compare == "<") {
    return leftValue < rightValue;
  } else if (compare == "<=") {
    return leftValue <= rightValue;
  } else if (compare == ">") {
    return leftValue > rightValue;
  } else if (compare == ">=") {
    return leftValue >= rightValue;
  } else if (compare == "=") {
    return leftValue == rightValue;
  } else if (compare == "!=") {
    return leftValue != rightValue;
  }
  CCASSERT(false, "unrecognize compare type");
}

string convertConditionStr(const string &str, const BaseData* associate)
{
  auto list = Utils::split(str, '.');
  auto type = list.at(0);
  list.erase(list.begin());
  return DataManager::getShareInstance()->decipherString(Utils::join(list, "."), associate);
}

int convertConditionStrToInt(const string &str, const BaseData* associate)
{
  auto list = Utils::split(str, '.');
  auto type = list.at(0);
  list.erase(list.begin());
  auto valueStr = DataManager::getShareInstance()->decipherString(Utils::join(list, "."), associate);
  int value = 0;
  if (type == "length") {
    value = valueStr.length();
  } else {
    value = atoi(valueStr.c_str());
  }
  return value;
}


bool Manager::checkConditionByString(const string &conditionStr, const BaseData* associate)
{
  // find the compare function
  auto compType = findCompareType(conditionStr);
  if (compType.length() > 0) {
    // if it split by ;
    if (compType == ";") {
      auto conditionList = Utils::split(conditionStr, ';');
      auto flag = true;
      for (auto str : conditionList) {
        flag = flag && checkConditionByString(str);
      }
      return flag;
    }
    // split by compType string
    auto pos = conditionStr.find(compType);
    auto leftStr = conditionStr.substr(0, pos);
    auto rightStr = conditionStr.substr(pos + compType.length());
    auto type = Utils::split(leftStr, '.').at(0);
    if (type == "int" || type == "length" || type == "bool") {
      auto leftValue = convertConditionStrToInt(leftStr, associate);
      auto rightValue = convertConditionStrToInt(rightStr, associate);
      return compareInteger(leftValue, rightValue, compType);
    } else if (type == "string") {
      auto leftValue = convertConditionStr(leftStr, associate);
      auto rightValue = convertConditionStr(rightStr, associate);
      return leftValue == rightValue;
    } else {
      CCLOGWARN("Un-recognized condition type: %s", type.c_str());
    }
  } else if (conditionStr.length() > 0 ) {
    auto type = Utils::split(conditionStr, '.').at(0);
    type = Utils::to_lower_string(type);
    if (type == "bool") {
      auto value = convertConditionStrToInt(conditionStr, associate);
      return value != 0;
    } else if (type == "data") {
      auto str = convertConditionStr(conditionStr, associate);
      return checkConditionByString(str);
    } else if (type == "false") {
      return false;
    } else {
      CCLOGWARN("Un-recognized condition string: %s", conditionStr.c_str());
    }
  }
  // default result is true
  return true;
}
