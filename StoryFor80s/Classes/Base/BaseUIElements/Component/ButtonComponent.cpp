//
//  ButtonComponent.cpp
//
//  Created by Yujie Liu on 9/23/18.
//

#include "ButtonComponent.hpp"
#include "BaseButton.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "BaseData.h"
#include "StoryJsonData.hpp"
#include "StoryManager.hpp"

USING_NS_CC;

ButtonComponent::ButtonComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_text = Utils::getStringFromJson(componentJson, "text");
  p_storyId = Utils::getStringFromJson(componentJson, "storyId");
  p_storyData = componentJson.count("story") ? StoryJsonData::createStoryData(componentJson.at("story")) : nullptr;
  p_textSize = Utils::getFloatFromJson(componentJson, "font_size", 0);
  p_imagePath = Utils::getStringFromJson(componentJson, "path");
  if (componentJson.count("setTemp")) {
    auto setTempJson = componentJson.at("setTemp");
    for (auto iter = setTempJson.begin(); iter != setTempJson.end(); ++iter) {
      auto key = iter.key();
      auto value = Utils::getStringFromJson(setTempJson, key);
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
  if (p_storyData != nullptr) {
    button->addClickEventListener([this](cocos2d::Ref* pSender) {
      StoryManager::getShareInstance()->startStory(p_storyData);
    });
  } else if (p_storyId.length() > 0) {
    auto storyId = p_storyId;
    button->addClickEventListener([storyId](cocos2d::Ref* pSender) {
      StoryManager::getShareInstance()->startStory(storyId);
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

ButtonComponent::~ButtonComponent()
{
  if (p_storyData != nullptr) {
    delete p_storyData;
  }
}
