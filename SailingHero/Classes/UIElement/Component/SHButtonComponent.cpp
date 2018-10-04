//
//  SHButtonComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/23/18.
//

#include "SHButtonComponent.hpp"
#include "SystemButton.hpp"
#include "EventManager.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"

USING_NS_CC;

SHButtonComponent::SHButtonComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_text = SHUtil::getStringFromJson(componentJson, "text");
  auto eventId = SHUtil::getStringFromJson(componentJson, "event");
  p_eventId = DataManager::getShareInstance()->decipherString(eventId);
}

Node* SHButtonComponent::addComponentToParent(unordered_map<string, Node *> &dict, cocos2d::Node *parent) const
{
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text) : "";
  auto button = SystemButton::defaultButtonWithText(text);
  if (p_eventId.size() > 0) {
    auto eventId = p_eventId;
    button->addClickEventListener([eventId](cocos2d::Ref* pSender) {
      EventManager::getShareInstance()->runEvent(eventId);
    });
  }

  addNodeToParent(dict, button, parent);
  
  return button;
}
