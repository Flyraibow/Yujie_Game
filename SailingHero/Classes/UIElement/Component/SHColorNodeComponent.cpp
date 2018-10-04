//
//  SHColorNodeComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHColorNodeComponent.hpp"
#include "SHColorNode.hpp"
#include "JsonUtil.hpp"

USING_NS_CC;

SHColorNodeComponent::SHColorNodeComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_color = SHUtil::getColorFromJson(componentJson, "backgroundColor");
}

Node* SHColorNodeComponent::addComponentToParent(unordered_map<string, Node *> &dict, cocos2d::Node *parent) const
{
  auto parentSize = parent->getContentSize();
  auto background = SHColorNode::create(p_color, parentSize.width, parentSize.height);

  addNodeToParent(dict, background, parent);

  return background;
}
