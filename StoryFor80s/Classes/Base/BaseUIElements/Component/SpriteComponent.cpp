//
//  SpriteComponent.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SpriteComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "BaseSpriteListener.hpp"
#include "StoryManager.hpp"

USING_NS_CC;

SpriteComponent::SpriteComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_iconPath = Utils::getStringFromJson(componentJson, "path");
  p_color = Utils::getColorFromJson(componentJson, "color");
  p_clickStoryEventId = Utils::getStringFromJson(componentJson, "click_event_id");
  p_tempDataKey = Utils::getStringFromJson(componentJson, "temp_data_key");
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
  
  if (p_clickStoryEventId.length() > 0) {
    auto listener = BaseSpriteListener::createWithNode(sprite);
    listener->setTouchEnd(CC_CALLBACK_2(SpriteComponent::clickSprite, this), nullptr);
  }

  addNodeToParent(dict, sprite, parent);
  
  return sprite;
}

void SpriteComponent::refresh()
{
  BaseComponent::refresh();
  if (p_iconPath.length() > 0) {
    auto sprite = dynamic_cast<Sprite *>(p_node);
    auto path = DataManager::getShareInstance()->decipherString(p_iconPath);
    sprite->setTexture(path);
  }
  for (auto component : p_componentList) {
    component->refresh();
  }
}

void SpriteComponent::clickSprite(Touch* touch, Event* event)
{
  CCLOG("start stories");
  if (p_tempDataKey.length() > 0) {
    DataManager::getShareInstance()->setTempData(p_tempDataKey, p_associateData);
  }
  StoryManager::getShareInstance()->startStory(p_clickStoryEventId);
}
