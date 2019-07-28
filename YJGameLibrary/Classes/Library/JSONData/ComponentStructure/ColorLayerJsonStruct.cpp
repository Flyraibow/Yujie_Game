//
//  ColorLayerJsonStruct.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "ColorLayerJsonStruct.hpp"
#include "JsonUtils+cocos2d.hpp"

ColorLayerJsonStruct::ColorLayerJsonStruct(const nlohmann::json &json) : NodeJsonStruct(json) {
  type = NodeTypeColorLayer;
  color = JsonUtils::getColorFromJson(json, "color");
}
