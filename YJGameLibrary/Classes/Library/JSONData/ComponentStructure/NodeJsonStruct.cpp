//
//  NodeJsonStruct.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "NodeJsonStruct.hpp"

const static unordered_map<string, NodePositionType> s_positionTypeMap ({
  {"full_screen", NodeFullScreen},
});

NodeJsonStruct::NodeJsonStruct(const nlohmann::json &json)
{
  auto positionType = JsonUtils::getStringFromJson(json, "positionType");
  p_positionType = s_positionTypeMap.count(positionType) ? s_positionTypeMap.at(positionType) : NodePositionDefault;
}

cocos2d::Size NodeJsonStruct::getContentSize() const
{
  switch (p_positionType) {
    case NodeFullScreen:
      return cocos2d::Director::getInstance()->getVisibleSize();
    default:
      break;
  };
  return cocos2d::Size();
}

#include "ColorLayerJsonStruct.hpp"

NodeJsonStruct* NodeJsonStruct::createNodeFromJson(const nlohmann::json &json)
{
  auto type = JsonUtils::getStringFromJson(json, "type");
  NodeJsonStruct* nodeStruct;
  if (type == "ColorLayer") {
    nodeStruct = new ColorLayerJsonStruct(json);
  } else {
    nodeStruct = new NodeJsonStruct(json);
  }
  return nodeStruct;
}
