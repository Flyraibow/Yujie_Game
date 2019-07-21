//
//  JsonUtils+cocos2d.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "JsonUtils+cocos2d.hpp"

cocos2d::Vec2 JsonUtils::getVec2FromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Vec2 &defaultValue)
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return cocos2d::Vec2(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

cocos2d::Size JsonUtils::getSizeFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Size &defaultValue)
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return cocos2d::Size(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

#include <unordered_map>

cocos2d::Color4B JsonUtils::getColorFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Color4B &defaultValue)
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
