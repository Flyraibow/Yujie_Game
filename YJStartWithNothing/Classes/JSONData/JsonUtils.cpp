//
//  JsonUtils.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "JsonUtils.hpp"

std::string JsonUtils::getStringFromJson(const nlohmann::json &json, const std::string &field, const std::string &defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<std::string>();
  }
  return defaultValue;
}

float JsonUtils::getFloatFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<float>();
  }
  return defaultValue;
}

float JsonUtils::getDoubleFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<double>();
  }
  return defaultValue;
}

int JsonUtils::getIntFromJson(const nlohmann::json &json, const std::string &field, const int defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<int>();
  }
  return defaultValue;
}

bool JsonUtils::getBoolFromJson(const nlohmann::json &json, const std::string &field, bool defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<bool>();
  }
  return defaultValue;
}

std::vector<std::string> JsonUtils::getStringListFromJson(const nlohmann::json &json, const std::string &field)
{
  std::vector<std::string> defaultValue;
  if (json.count(field)) {
    auto vec = json.at(field);
    for (auto content : vec) {
      defaultValue.push_back(content.get<std::string>());
    }
  }
  return defaultValue;
}

std::vector<nlohmann::json> JsonUtils::getJsonListFromJson(const nlohmann::json &json, const std::string &field)
{
  std::vector<nlohmann::json> defaultValue;
  if (json.count(field)) {
    auto vec = json.at(field);
    for (auto content : vec) {
      defaultValue.push_back(content.get<nlohmann::json>());
    }
  }
  return defaultValue;
}

std::pair<double, double> JsonUtils::getPositionPairFromJson(const nlohmann::json &json, const std::string &field, const std::pair<double, double> &defaultValue)
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return std::make_pair(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

nlohmann::json JsonUtils::getChildJsonFromJson(const nlohmann::json &json, const std::string &field)
{
  if (json.count(field)) {
    return json.at(field);
  }
  return nlohmann::json();
}

std::vector<std::string> JsonUtils::getKeysFromJson(const nlohmann::json &json)
{
  std::vector<std::string> keys;
  for (auto iter = json.begin(); iter != json.end(); ++iter) {
    auto key = iter.key();
    keys.push_back(key);
  }
  return keys;
}
