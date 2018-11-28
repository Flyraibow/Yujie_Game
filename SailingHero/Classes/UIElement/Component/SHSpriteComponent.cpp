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
  p_iconPath = SHUtil::getStringFromJson(componentJson, "path");
}

Node* SHSpriteComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  Sprite *sprite;
  if (p_iconPath.length() > 0) {
    auto path = DataManager::getShareInstance()->decipherString(p_iconPath);
    sprite = Sprite::create(path);
  }

  addNodeToParent(dict, sprite, parent);
  
  return sprite;
}

void SHSpriteComponent::refresh()
{
  SHComponent::refresh();
  auto sprite = dynamic_cast<Sprite *>(p_node);
  auto path = DataManager::getShareInstance()->decipherString(p_iconPath);
  sprite->setTexture(path);
  for (auto component : p_componentList) {
    component->refresh();
  }
}
