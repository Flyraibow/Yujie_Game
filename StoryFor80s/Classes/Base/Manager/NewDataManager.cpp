//
//  NewDataManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 4/30/19.
//

#include "NewDataManager.hpp"
#include "LocalizationHelper.hpp"
#include "Utils.hpp"

pair<int, int> findFirstParenthesis(const string &str)
{
  int leftIndex = -1;
  for (int i = 0; i < str.size(); ++i) {
    char c = str.at(i);
    if (c == ')') {
      CCASSERT(leftIndex >= 0, "there is no left '(' for right ')'");
      return make_pair(leftIndex, i);
    } else if (c == '(') {
      leftIndex = i;
    }
  }
  return make_pair(-1, -1);
}

enum KeyType {
  Undefined,
  Temp,             // Temporary string, saved in temporary
  Translation,      // Translation string, will read it from translation directly
  
};

const unordered_map<string, KeyType> s_mapKeyTypes = {
  {"translation",Translation},
};

KeyType getKeyTypeFromStr(const string &str)
{
  if (s_mapKeyTypes.count(str)) {
    return s_mapKeyTypes.at(str);
  }
  return Undefined;
}


string NewDataManager::decipherNoParenthesisString(const string &str, const BaseData *associateData) const
{
  // We should Only pass a string without parenthesis
  auto args = Utils::split(str, '.');
  if (args.size() > 1) {
    auto key = getKeyTypeFromStr(args.at(0));
    switch (key) {
      case Translation:
        return LocalizationHelper::getLocalization(args.at(1));
        break;
      default:
        CCLOGERROR("Unabled to recognize string : %s", str.c_str());
        break;
    }
  }
  return str;
}

string NewDataManager::decipherParenthesis(const string &str, const BaseData *associateData) const
{
  auto strValue = str;
  pair<int, int> parenthesis = findFirstParenthesis(strValue);
  if (parenthesis.first >= 0) {
    auto leftIndex = parenthesis.first;
    auto rightIndex = parenthesis.second;
    string subStr = decipherNoParenthesisString(strValue.substr(leftIndex + 1, rightIndex - 1 - leftIndex), associateData);
    string newValue = strValue;
    newValue.replace(leftIndex, rightIndex - leftIndex + 1, subStr);
    return decipherParenthesis(newValue, associateData);
  }
  return strValue;
}

BaseData* NewDataManager::decipherData(const string &str, const BaseData *associateData) const
{
  auto valueStr = decipherParenthesis(str, associateData);
}

vector<BaseData*> NewDataManager::decipherDataList(const string &str, const BaseData *associateData) const
{
  auto valueStr = decipherParenthesis(str, associateData);
}

string NewDataManager::decipherString(const string &str, const BaseData *associateData) const
{
  auto valueStr = decipherParenthesis(str, associateData);
}

bool NewDataManager::decipherCondition(const string &str, const BaseData *associateData) const
{
  auto valueStr = decipherParenthesis(str, associateData);
  
}
