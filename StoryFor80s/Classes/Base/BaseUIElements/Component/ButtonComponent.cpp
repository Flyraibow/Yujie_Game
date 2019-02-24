//
//  ButtonComponent.cpp
//
//  Created by Yujie Liu on 9/23/18.
//

#include "ButtonComponent.hpp"
#include "BaseButton.hpp"
#include "EventManager.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "BaseData.h"

USING_NS_CC;

ButtonComponent::ButtonComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_text = Utils::getStringFromJson(componentJson, "text");
  p_eventId = Utils::getStringFromJson(componentJson, "event");
  p_textSize = Utils::getFloatFromJson(componentJson, "font_size", 0);
  p_imagePath = Utils::getStringFromJson(componentJson, "path");
  if (componentJson.count("setTemp")) {
    auto setTempJson = componentJson.at("setTemp");
    for (auto iter = setTempJson.begin(); iter != setTempJson.end(); ++iter) {
      auto key = iter.key();
      auto value = Utils::getStringFromJson(setTempJson, key);;
      p_setTempStrDict.insert(make_pair(key, value));
    }
  }
}

Node* ButtonComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  ui::Button* button = nullptr;
  auto text = p_text.size() > 0 ? decipherValue(p_text) : "";
  if (p_imagePath.length() > 0) {
    auto path = decipherValue(p_imagePath);
    button = ui::Button::create(path);
    button->setTitleText(text);
  } else {
    button = BaseButton::defaultButtonWithText(text);
  }
  if (p_textSize > 0) {
    button->setTitleFontSize(p_textSize);
  }
  auto size = getComponentSize(parent);
  if (size.height > 0 && size.width > 0) {
    button->setContentSize(size);
  }
  if (p_eventId.size() > 0) {
    auto eventId = decipherValue(p_eventId);
    auto associateData = p_associateData;
    auto setTempStrDict = p_setTempStrDict;
    button->addClickEventListener([eventId, associateData, setTempStrDict](cocos2d::Ref* pSender) {
      if (setTempStrDict.size() > 0) {
        for (auto iter = setTempStrDict.begin(); iter != setTempStrDict.end(); ++iter) {
          auto value = DataManager::getShareInstance()->decipherString(iter->second);
          DataManager::getShareInstance()->setTempString(iter->first, value);
        }
      }
      if (associateData != nullptr) {
        DataManager::getShareInstance()->setTempData("clickData", associateData);
        CCLOG("%s", associateData->description().c_str());
      }
      EventManager::getShareInstance()->runEvent(eventId);
    });
  }

  addNodeToParent(dict, button, parent);
  
  return button;
}

void ButtonComponent::refresh()
{
  if (p_shouldHideCondition.length() > 0) {
    p_node->setVisible(!DataManager::getShareInstance()->checkCondition(p_shouldHideCondition));
  }
}
