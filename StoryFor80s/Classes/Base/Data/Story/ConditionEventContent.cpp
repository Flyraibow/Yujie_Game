//
//  ConditionEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "ConditionEventContent.hpp"
#include "StoryJsonData.hpp"
#include "ConditionManager.hpp"
#include "StoryManager.hpp"

#include "JsonUtil.hpp"

ConditionEventContent::~ConditionEventContent()
{
  if (p_noEventData != nullptr) {
    delete p_noEventData;
  }
  if (p_yesEventData != nullptr) {
    delete p_yesEventData;
  }
}

ConditionEventContent::ConditionEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_conditionStr = Utils::getStringFromJson(jsonContent, "condition");
  p_yesEventId = Utils::getStringFromJson(jsonContent, "yes_story_id");
  p_noEventId = Utils::getStringFromJson(jsonContent, "no_story_id");
  p_noEventData = jsonContent.count("no_story") ? StoryJsonData::createStoryData(jsonContent.at("no_story")) : nullptr;
  p_yesEventData = jsonContent.count("yes_story") ? StoryJsonData::createStoryData(jsonContent.at("yes_story")) : nullptr;
}

void ConditionEventContent::runEvent(StoryEventCallback callback)
{
  if (Manager::checkConditionByString(p_conditionStr)) {
    if (p_yesEventData != nullptr) {
      StoryManager::getShareInstance()->startStory(p_yesEventData);
    } else if (p_yesEventId.length() > 0) {
      StoryManager::getShareInstance()->startStory(p_yesEventId);
    }
  } else {
    if (p_noEventData != nullptr) {
      StoryManager::getShareInstance()->startStory(p_noEventData);
    } else if (p_noEventId.length() > 0) {
      StoryManager::getShareInstance()->startStory(p_noEventId);
    }
  }
  if (!p_noCallback){
    callback();
  }
}
