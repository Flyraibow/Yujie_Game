//
//  NodeJsonStruct.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "NodeJsonStruct.hpp"

NodeJsonStruct::NodeJsonStruct(const nlohmann::json &json)
{
  
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
