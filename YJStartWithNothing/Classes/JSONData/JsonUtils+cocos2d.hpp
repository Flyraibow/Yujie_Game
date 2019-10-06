//
//  JsonUtils+cocos2d.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef JsonUtils_cocos2d_hpp
#define JsonUtils_cocos2d_hpp

#include "json.hpp"
#include "cocos2d.h"

namespace JsonUtils {
  cocos2d::Vec2 getVec2FromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Vec2 &defaultValue = cocos2d::Vec2());
  cocos2d::Size getSizeFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Size &defaultValue = cocos2d::Size());
  cocos2d::Color4B getColorFromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Color4B &defaultValue = cocos2d::Color4B());
}

#endif /* JsonUtils_cocos2d_hpp */
