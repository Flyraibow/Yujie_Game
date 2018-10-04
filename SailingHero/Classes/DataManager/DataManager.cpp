//
//  DataManager.cpp
//  SailingHero
//
//  Created by Yujie Liu on 10/3/18.
//

#include "DataManager.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"

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

void DataManager::setDataValue(const string &key, const string &field, const string &value)
{
  auto data = decipherData(key);
  if (data != nullptr) {
    data->setFieldValue(field, decipherString(value));
  } else {
    CCLOGWARN("Couldn't find data from key : %s", key.c_str());
  }
}

BaseData* DataManager::decipherData(const string &value) const
{
  auto args = SHUtil::split(value, '.');
  if (args.size() > 1) {
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

string DataManager::decipherString(const string &value) const
{
  auto args = SHUtil::split(value, '.');
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
    } else if (k == "data") {
      auto dataKey = args.at(1);
      if (p_tempDataMap.count(dataKey)) {
        if (args.size() > 2) {
          val = p_tempDataMap.at(dataKey)->getFieldValue(args.at(2));
        } else {
          val = p_tempDataMap.at(dataKey)->description();
        }
      } else {
        CCLOGWARN("Cannot decipher value : %s", value.c_str());
      }
    }
  }
  return val;
}
