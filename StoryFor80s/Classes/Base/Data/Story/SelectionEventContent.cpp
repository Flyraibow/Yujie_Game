//
//  SelectionEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/2/19.
//

#include "SelectionEventContent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "ConditionManager.hpp"
#include "StoryJsonData.hpp"
#include "BaseButtonGroup.hpp"
#include "SceneManager.hpp"
#include "StoryManager.hpp"


SelectionElement::SelectionElement(const nlohmann::json &jsonContent)
{
  p_condition = Utils::getStringFromJson(jsonContent, "condition");
  p_text = Utils::getStringFromJson(jsonContent, "text");
  p_autoClose = Utils::getBoolFromJson(jsonContent, "auto_close", true);
  p_subStoryData = jsonContent.count("events") ? StoryJsonData::createStoryData(jsonContent) : nullptr;
  if (p_subStoryData == nullptr) {
    if (jsonContent.count("story_id")) {
      p_subStoryData = StoryJsonData::createStoryData(Utils::getStringFromJson(jsonContent, "story_id"));
    } else if (jsonContent.count("story")) {
      p_subStoryData = StoryJsonData::createStoryData(jsonContent.at("story"));
    }
  }
}

bool SelectionElement::isAutoClose() const
{
  return p_autoClose;
}

SelectionElement::~SelectionElement()
{
  if (p_subStoryData != nullptr) {
    delete p_subStoryData;
    p_subStoryData = nullptr;
  }
}

bool SelectionElement::isCondtionFufilled() const
{
  return Manager::checkConditionByString(p_condition);
}

string SelectionElement::getText() const
{
  return DataManager::getShareInstance()->decipherString(p_text);
}

StoryJsonData *SelectionElement::getStoryData() const
{
  return p_subStoryData;
}

SelectionEventContent::SelectionEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  CCASSERT(jsonContent.count("selections"), "Selection event must have selections");
  auto selections = jsonContent.at("selections");
  for (int i = 0; i < selections.size(); ++i) {
    nlohmann::json selectionJson = selections.at(i);
    SelectionElement *selectionElement = new SelectionElement(selectionJson);
    p_selectionElements.push_back(selectionElement);
  }
  p_backgroundColor = Utils::getColorFromJson(jsonContent, "background_color");
}

SelectionEventContent::~SelectionEventContent()
{
  for (auto selectionElement : p_selectionElements) {
    delete selectionElement;
  }
  p_selectionElements.clear();
}

void SelectionEventContent::runEvent(StoryEventCallback callback)
{
  vector<BaseButton *> buttons;
  for (auto selection : p_selectionElements) {
    if (selection->isCondtionFufilled()) {
      auto button = BaseButton::defaultButtonWithText(selection->getText());
      button->addClickEventListener([selection, callback, this](cocos2d::Ref* pSender) {
        if (selection->isAutoClose()) {
          this->p_buttonGroup->removeFromParent();
        }
        if (selection->getStoryData() != nullptr) {
          StoryManager::getShareInstance()->startStory(selection->getStoryData());
        }
        callback();
      });
      buttons.push_back(button);
    }
  }
  if (buttons.size() > 0) {
    p_buttonGroup = BaseButtonGroup::create(buttons, GroupButtonOptionItalic | GroupButtonOptionAlignAll, p_backgroundColor);
    auto baseScene = SceneManager::getShareInstance()->currentScene();
    baseScene->addChild(p_buttonGroup, SCREEN_DIALOG_LAYER);
  } else {
    callback();
  }
}
