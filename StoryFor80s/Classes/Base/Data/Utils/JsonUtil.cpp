//
//  JsonUtil.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "JsonUtil.hpp"

cocos2d::Vec2 Utils::getVec2FromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Vec2 &defaultValue)
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return cocos2d::Vec2(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

cocos2d::Size Utils::getSizeFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Size &defaultValue)
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return cocos2d::Size(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

std::string Utils::getStringFromJson(const nlohmann::json &json, const std::string &field, const std::string &defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<std::string>();
  }
  return defaultValue;
}

#include <unordered_map>

cocos2d::Color4B Utils::getColorFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Color4B &defaultValue)
{
  if (json.count(field)) {
    auto j = json.at(field);
    if (j.is_array()) {
      if (j.size() == 3) {
        return cocos2d::Color4B(cocos2d::Color3B(j.at(0), j.at(1), j.at(2)));
      } else {
        CCASSERT(j.size() == 4, ("Color must be (R G B A) format, it's " + j.dump()).c_str());
        return cocos2d::Color4B(j.at(0), j.at(1), j.at(2), j.at(3));
      }
    } else if (j.is_string()) {
      static const std::unordered_map<std::string, cocos2d::Color4B> COLOR_MAP = {
        {"BLACK", cocos2d::Color4B::BLACK},
        {"GRAY", cocos2d::Color4B::GRAY},
        {"BLUE", cocos2d::Color4B::BLUE},
        {"GREEN", cocos2d::Color4B::GREEN},
        {"YELLOW", cocos2d::Color4B::YELLOW},
        {"RED", cocos2d::Color4B::RED},
        {"WHITE", cocos2d::Color4B::WHITE},
        {"ORANGE", cocos2d::Color4B::ORANGE},
        {"MAGENTA", cocos2d::Color4B::MAGENTA},
        {"alpha_black", cocos2d::Color4B(cocos2d::Color3B::BLACK, 100)},
        {"alpha_red", cocos2d::Color4B(cocos2d::Color3B::RED, 100)},
        {"alpha_blue", cocos2d::Color4B(cocos2d::Color3B::BLUE, 100)},
        {"alpha_green", cocos2d::Color4B(cocos2d::Color3B::GREEN, 100)},
        {"alpha_white", cocos2d::Color4B(cocos2d::Color3B::WHITE, 100)},
        {"alpha_zero", cocos2d::Color4B(cocos2d::Color3B::WHITE, 0)},
      };
      
      CCASSERT(COLOR_MAP.count(j), ("Color must be color string, it's " + j.dump()).c_str());
      return COLOR_MAP.at(j);
    }
  }
  return defaultValue;
}

float Utils::getFloatFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<float>();
  }
  return defaultValue;
}

float Utils::getDoubleFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<double>();
  }
  return defaultValue;
}

int Utils::getIntFromJson(const nlohmann::json &json, const std::string &field, const int defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<int>();
  }
  return defaultValue;
}

bool Utils::getBoolFromJson(const nlohmann::json &json, const std::string &field, bool defaultValue)
{
  if (json.count(field)) {
    return json.at(field).get<bool>();
  }
  return defaultValue;
}

std::vector<std::string> Utils::getStringListFromJson(const nlohmann::json &json, const std::string &field)
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

std::vector<nlohmann::json> Utils::getJsonListFromJson(const nlohmann::json &json, const std::string &field)
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


TextJsonInfo Utils::getTextInfoFromJson(const nlohmann::json &json, const std::string &field)
{
  TextJsonInfo textInfo;
  auto jsonContent = json.at(field);
  textInfo.text = getStringFromJson(jsonContent, "text");
  textInfo.size = getFloatFromJson(jsonContent, "size", 20);
  textInfo.typingSpeed = getIntFromJson(jsonContent, "speed");
  textInfo.textColor = getColorFromJson(jsonContent, "color");
  textInfo.typingEffect = getStringFromJson(jsonContent, "typingEffect");
  return textInfo;
}
