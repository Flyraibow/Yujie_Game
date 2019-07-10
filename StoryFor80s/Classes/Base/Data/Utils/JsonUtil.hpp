//
//  JsonUtil.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef JsonUtil_hpp
#define JsonUtil_hpp

#include "json.hpp"
#include "cocos2d.h"
#include "TextJsonInfo.hpp"

namespace Utils {
  cocos2d::Vec2 getVec2FromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Vec2 &defaultValue = cocos2d::Vec2());
  cocos2d::Size getSizeFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Size &defaultValue = cocos2d::Size());
  std::string getStringFromJson(const nlohmann::json &json, const std::string &field, const std::string &defaultValue = "");
  int getIntFromJson(const nlohmann::json &json, const std::string &field, const int defaultValue = 0);
  float getFloatFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue = 0);
  float getDoubleFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue = 0);
  bool getBoolFromJson(const nlohmann::json &json, const std::string &field, bool defaultValue = false);
  cocos2d::Color4B getColorFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Color4B &defaultValue = cocos2d::Color4B());
  std::vector<std::string> getStringListFromJson(const nlohmann::json &json, const std::string &field);
  std::vector<nlohmann::json> getJsonListFromJson(const nlohmann::json &json, const std::string &field);
  TextJsonInfo getTextInfoFromJson(const nlohmann::json &json, const std::string &field);
}

#endif /* JsonUtil_hpp */
