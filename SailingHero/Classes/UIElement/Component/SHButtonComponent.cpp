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
  p_eventId = SHUtil::getStringFromJson(componentJson, "event");
  p_textSize = SHUtil::getFloatFromJson(componentJson, "font_size", 0);
  p_imagePath = SHUtil::getStringFromJson(componentJson, "path");
}

Node* SHButtonComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  ui::Button* button = nullptr;
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text) : "";
  if (p_imagePath.length() > 0) {
    auto path = DataManager::getShareInstance()->decipherString(p_imagePath);
    button = ui::Button::create(path);
    button->setTitleText(text);
  } else {
    button = SystemButton::defaultButtonWithText(text);
  }
  if (p_textSize > 0) {
    button->setTitleFontSize(p_textSize);
  }
  auto size = getComponentSize(parent);
  if (size.height > 0 && size.width > 0) {
    button->setContentSize(size);
  }
  if (p_eventId.size() > 0) {
    auto eventId = DataManager::getShareInstance()->decipherString(p_eventId);
    button->addClickEventListener([eventId](cocos2d::Ref* pSender) {
      EventManager::getShareInstance()->runEvent(eventId);
    });
  }

  addNodeToParent(dict, button, parent);
  
  return button;
}
