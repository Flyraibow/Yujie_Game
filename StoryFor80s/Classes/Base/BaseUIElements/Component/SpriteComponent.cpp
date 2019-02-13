//
//  SpriteComponent.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SpriteComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"

USING_NS_CC;

SpriteComponent::SpriteComponent(nlohmann::json componentJson) : BaseComponent(componentJson)
{
  p_iconPath = SHUtil::getStringFromJson(componentJson, "path");
  p_color = SHUtil::getColorFromJson(componentJson, "color");
}

Node* SpriteComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  Sprite *sprite;
  if (p_iconPath.length() > 0) {
    auto path = DataManager::getShareInstance()->decipherString(p_iconPath);
    sprite = Sprite::create(path);
  } else {
    auto size = getComponentSize(parent);
    sprite = Sprite::create();
    sprite->setContentSize(size);
    auto colorLayer = LayerColor::create(p_color, size.width, size.height);
    sprite->addChild(colorLayer);
  }

  addNodeToParent(dict, sprite, parent);
  
  return sprite;
}

void SpriteComponent::refresh()
{
  BaseComponent::refresh();
  auto sprite = dynamic_cast<Sprite *>(p_node);
  auto path = DataManager::getShareInstance()->decipherString(p_iconPath);
  sprite->setTexture(path);
  for (auto component : p_componentList) {
    component->refresh();
  }
}
