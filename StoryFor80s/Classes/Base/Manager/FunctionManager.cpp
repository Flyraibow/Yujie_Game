//
//  FunctionManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/16/19.
//

#include "FunctionManager.hpp"
#include "DataManager.hpp"
#include "ConditionManager.hpp"
#include "FunctionCalculationData.hpp"
#include "LocalizationHelper.hpp"
#include "Utils.hpp"
#include <unordered_set>

string getFormatStringFromFunction(FunctionCalculationData *functionData)
{
  auto parameters = functionData->getParameters();
  if (parameters.size() == 0) {
    CCLOGERROR("string_format should take at list one argument: %s", functionData->getFunctionCalculatonId().c_str());
  } else {
    auto localStr = LocalizationHelper::getLocalization(parameters.at(0));
    auto params = parameters;
    params.erase(params.begin());
    return DataManager::getShareInstance()->formatStringWithParamters(localStr, params);
  }
  return "failed to load " + functionData->getFunctionCalculatonId();
}

pair<char, int> getNextCalculationFunction(const string &str, int fromIndex = 0)
{
  const static unordered_set<char> calChar({'+', '-'});
  for (int i = fromIndex; i < str.length(); ++i) {
    char c = str.at(i);
    if (calChar.count(c)) {
      return make_pair(c, i);
    }
  }
  return make_pair(' ', -1);
}

int Manager::calculateIntFromFunction(const string &calString)
{
  int index = 0;
  int result = 0;
  char lastCalFunc = '+';
  while (index < calString.length()) {
    auto pairCharIndex = getNextCalculationFunction(calString, index);
    string subStr;
    if (pairCharIndex.second >= 0) {
      subStr = calString.substr(index, pairCharIndex.second - index);
    } else {
      subStr = calString.substr(index);
    }
    int subStrValue = subStr.length() > 0 ? atoi(DataManager::getShareInstance()->decipherString(subStr).c_str()) : 0;
    if (lastCalFunc == '+') {
      result += subStrValue;
    } else if (lastCalFunc == '-') {
      result -= subStrValue;
    }
    if (pairCharIndex.second >= 0) {
      lastCalFunc = pairCharIndex.first;
      index = pairCharIndex.second + 1;
    } else {
      break;
    }
  }
  return result;
}

string Manager::getFunctionValueById(const string &functionId)
{
  auto functionData = FunctionCalculationData::getFunctionCalculationDataById(functionId);
  auto functionName = functionData->getFunctionName();
  auto paramters = functionData->getParameters();
  string val;
  if (functionName == "string_connect") {
    for (auto str : paramters) {
      val += DataManager::getShareInstance()->decipherString(str);
    }
  } else if (functionName == "string_format") {
    val = getFormatStringFromFunction(functionData);
  } else if (functionName == "condition") {
    auto conditionString = paramters.at(0);
    string result;
    if (checkConditionByString(conditionString)) {
      result = DataManager::getShareInstance()->decipherString(paramters.at(1));
    } else {
      result = DataManager::getShareInstance()->decipherString(paramters.at(2));
    }
    return result;
  } else if (functionName == "calculation") {
    auto calString = paramters.at(0);
    if (functionData->getReturnType() == "int") {
      auto result = calculateIntFromFunction(calString);
      val = to_string(result);
    } else {
      CCLOGERROR("function id: %s, unrecognized return type:%s", functionId.c_str(), functionData->getReturnType().c_str());
    }
  } else {
    CCLOGERROR("unrecognized function id: %s", functionId.c_str());
  }
  return val;
}

string Manager::getFunctionValueById(const string &functionId, BaseData *data)
{
  DataManager::getShareInstance()->setTempData("temp", data);
  return getFunctionValueById(functionId);
}

BaseData* Manager::getFunctionDataById(const string &functionId)
{
  return nullptr;
}
