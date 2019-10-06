//
//  EventData.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/5/19.
//

#include "EventData.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"
#include "GameManager.hpp"
#include "BaseSpriteListener.hpp"

const static std::string SYSTEM_FONT = "Helvetica";


ValueChangeData::ValueChangeData(const nlohmann::json &valueJson)
{
  p_type = JsonUtils::getStringFromJson(valueJson, "type");
  p_value = JsonUtils::getDoubleFromJson(valueJson, "value");
  p_length = JsonUtils::getDoubleFromJson(valueJson, "length");
  p_isInstant = JsonUtils::getBoolFromJson(valueJson, "instant");
}


OptionData::OptionData(const nlohmann::json &eventJson)
{
  p_text = JsonUtils::getStringFromJson(eventJson, "text");
  auto valuesList = JsonUtils::getJsonListFromJson(eventJson, "values");
  p_isSelected = false;
  for (auto valueJson : valuesList) {
    auto valueData = new ValueChangeData(valueJson);
    p_values.push_back(valueData);
  }
}

bool OptionData::clickOption(Touch* touch, Event* event)
{
  if (!p_parentEvent->isNotSelected()) {
    return false;
  }
  if (p_weakLab != nullptr) {
    p_weakLab->setTextColor(Color4B::RED);
  }
  for (auto valueChange : p_values) {
    GameManager::getInstance()->valueChange(valueChange);
  }
  p_isSelected = true;
  return true;
}

OptionData::~OptionData()
{
  for (auto value : p_values) {
    delete value;
  }
  p_values.clear();
}

ConditionData::ConditionData(const nlohmann::json &conditionJson)
{
  p_type = JsonUtils::getStringFromJson(conditionJson, "type");
  p_compareMethod = JsonUtils::getStringFromJson(conditionJson, "compare");
  p_value = JsonUtils::getDoubleFromJson(conditionJson, "value");
}

ConditionData::~ConditionData()
{
  
}

bool ConditionData::pass() const
{
  auto curVal = GameManager::getInstance()->getTypeValue(p_type);
  if (p_compareMethod == ">") {
    return curVal > p_value;
  }
  return false;
}

EventData::EventData(const nlohmann::json &eventJson)
{
  p_eventName = JsonUtils::getStringFromJson(eventJson, "name");
  p_age = JsonUtils::getDoubleFromJson(eventJson, "age");
  p_distantAge = JsonUtils::getDoubleFromJson(eventJson, "distance");
  p_text = JsonUtils::getStringFromJson(eventJson, "text");
  p_height = JsonUtils::getDoubleFromJson(eventJson, "height");
  p_force = JsonUtils::getBoolFromJson(eventJson, "force");
  p_status = 0;
  
  auto optionsList = JsonUtils::getJsonListFromJson(eventJson, "options");
  for (auto optionJson : optionsList) {
    auto optionData = new OptionData(optionJson);
    optionData->setParentEvent(this);
    p_options.push_back(optionData);
  }
  auto valuesList = JsonUtils::getJsonListFromJson(eventJson, "values");
  for (auto valueJson : valuesList) {
    auto valueData = new ValueChangeData(valueJson);
    p_values.push_back(valueData);
  }
  auto conditionList = JsonUtils::getJsonListFromJson(eventJson, "conditions");
  for (auto conditionJson : conditionList) {
    auto conditionData = new ConditionData(conditionJson);
    p_conditions.push_back(conditionData);
  }
  p_node = nullptr;
}

EventData::~EventData()
{
  GameManager::getInstance()->removeEvent(this);
  for (auto optionData : p_options) {
    delete optionData;
  }
  p_options.clear();
  if (p_node != nullptr) {
    if (p_node->getParent() != nullptr) {
      p_node->removeFromParent();
    }
  }
  p_node = nullptr;
}

Node* EventData::getNode()
{
  if (p_node != nullptr && p_node->getParent() != nullptr) {
    return p_node;
  }
  p_node = Node::create();
  if (p_text.length() > 0) {
    auto lab = Label::createWithSystemFont(p_text, SYSTEM_FONT, 20);
    lab->setTextColor(Color4B::BLACK);
    p_node->addChild(lab);
  }
  if (p_options.size() > 0) {
    int i = 0;
    for (auto option : p_options) {
      auto optionLab = Label::createWithSystemFont(option->getText(), SYSTEM_FONT, 20);
      optionLab->setTextColor(Color4B::BLUE);
      optionLab->setPosition(0, optionLab->getContentSize().height * (- i - 1));
      option->setLabel(optionLab);
      auto listener = BaseSpriteListener::createWithNode(optionLab, false);
      listener->setTouchBegin(CC_CALLBACK_2(OptionData::clickOption, option));
      p_node->addChild(optionLab);
      ++i;
    }
  }
  return p_node;
}

bool EventData::isNotSelected() const
{
  for (auto option : p_options) {
    if (!option->isNotSelected()) {
      return false;
    }
  }
  return true;
}

void EventData::forceSelect()
{
  if (p_options.size() > 0) {
    p_options.at(0)->clickOption(nullptr, nullptr);
  }
}

bool EventData::passCondition() const
{
  bool flag = true;
  for (auto condition : p_conditions) {
    flag = flag & condition->pass();
  }
  return flag;
}
