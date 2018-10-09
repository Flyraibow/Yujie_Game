//
//  SHSpriteComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHSpriteComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"

USING_NS_CC;

SHSpriteComponent::SHSpriteComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  auto path = SHUtil::getStringFromJson(componentJson, "path");
  p_iconPath = DataManager::getShareInstance()->decipherString(path);
}

Node* SHSpriteComponent::addComponentToParent(unordered_map<string, Node *> &dict, cocos2d::Node *parent) const
{
  Sprite *sprite;
  if (p_iconPath.length() > 0) {
    sprite = Sprite::create(p_iconPath);
  }

  addNodeToParent(dict, sprite, parent);
  
  return sprite;
}
