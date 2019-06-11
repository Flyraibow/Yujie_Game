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
#include "ConditionManager.hpp"

USING_NS_CC;

ButtonComponent::ButtonComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_text = Utils::getStringFromJson(componentJson, "text");
  p_storyData = componentJson.count("story") ? StoryJsonData::createStoryData(componentJson.at("story")) : nullptr;
  p_storyId = Utils::getStringFromJson(componentJson, "storyId");
  if (p_storyData == nullptr && p_storyId.length() > 0) {
    p_storyData = StoryJsonData::createStoryData(p_storyId);
  }
  p_textSize = Utils::getFloatFromJson(componentJson, "font_size", 0);
  p_imagePath = Utils::getStringFromJson(componentJson, "path");
  p_disableCondition = Utils::getStringFromJson(componentJson, "disable_condition");
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
      for (auto iter = p_setTempStrDict.begin(); iter != p_setTempStrDict.end(); ++iter) {
        auto value = DataManager::getShareInstance()->decipherString(iter->second);
        DataManager::getShareInstance()->setTempString(iter->first, value);
      }
      StoryManager::getShareInstance()->startStory(p_storyData);
    });
  }
  if (p_disableCondition.length() > 0) {
    button->setEnabled(Manager::checkConditionByString(p_disableCondition));
  }

  addNodeToParent(dict, button, parent);
  
  return button;
}

void ButtonComponent::refresh()
{
  checkHideCondition();
  auto button = dynamic_cast<ui::Button *>(p_node);
  if (p_disableCondition.length() > 0) {
    button->setEnabled(Manager::checkConditionByString(p_disableCondition));
  }
  auto text = p_text.size() > 0 ? decipherValue(p_text) : "";
  button->setTitleText(text);
}

ButtonComponent::~ButtonComponent()
{
  if (p_storyData != nullptr) {
    delete p_storyData;
  }
  BaseComponent::~BaseComponent();
}
