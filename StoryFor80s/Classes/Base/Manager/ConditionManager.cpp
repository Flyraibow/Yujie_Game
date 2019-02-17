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
  if (conditionStr.find("<=") != string::npos) {
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

int convertConditionStrToInt(const string &str)
{
  auto list = SHUtil::split(str, '.');
  auto type = list.at(0);
  list.erase(list.begin());
  auto valueStr = DataManager::getShareInstance()->decipherString(SHUtil::join(list, "."));
  int value = 0;
  if (type == "length") {
    value = valueStr.length();
  } else {
    value = atoi(valueStr.c_str());
  }
  return value;
}


bool Manager::checkConditionByString(const string &conditionStr)
{
  // find the compare function
  auto compType = findCompareType(conditionStr);
  if (compType.length() > 0) {
    // split by compType string
    auto pos = conditionStr.find(compType);
    auto leftStr = conditionStr.substr(0, pos);
    auto rightStr = conditionStr.substr(pos + compType.length());
    auto type = SHUtil::split(leftStr, '.').at(0);
    if (type == "int" || type == "length") {
      auto leftValue = convertConditionStrToInt(leftStr);
      auto rightValue = convertConditionStrToInt(rightStr);
      return compareInteger(leftValue, rightValue, compType);
    } else if (type == "string") {
      
    } else {
      CCLOGWARN("Un-recognized condition type: %s", type.c_str());
    }
  } else {
    CCLOGWARN("Un-recognized condition string: %s", conditionStr.c_str());
  }
  // default result is true
  return true;
}
