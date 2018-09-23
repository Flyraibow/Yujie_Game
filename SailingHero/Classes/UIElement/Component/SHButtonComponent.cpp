//
//  SHButtonComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/23/18.
//

#include "SHButtonComponent.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "EventManager.hpp"

USING_NS_CC;

SHButtonComponent::SHButtonComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  if (componentJson.count("text")) {
    p_text = componentJson.at("text").get<std::string>();
  }
  if (componentJson.count("event")) {
    p_eventId = componentJson.at("event").get<std::string>();
  }
}

Node *SHButtonComponent::generateComponent()
{
  auto text = p_text.size() > 0 ? LocalizationHelper::getLocalization(p_text) : "";
  auto button = SystemButton::defaultButtonWithText(text);
  if (p_eventId.size() > 0) {
    auto eventId = p_eventId;
    button->addClickEventListener([eventId](cocos2d::Ref* pSender) {
      EventManager::getShareInstance()->runEvent(eventId);
    });
  }
  button->setName(p_id);
  button->setAnchorPoint(p_anchorPoint);
  button->setNormalizedPosition(p_normalizePosition);
  return button;
}
