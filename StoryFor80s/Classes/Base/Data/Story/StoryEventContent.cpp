//
//  StoryEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "StoryEventContent.hpp"
#include "JsonUtil.hpp"

vector<StoryEventContent *> StoryEventContent::getStoryEventsFromJson(const nlohmann::json &jsonContent)
{
  vector<StoryEventContent *> result;
  if (jsonContent.count("events")) {
    auto storyEventsJsonList = jsonContent.at("events");
    for (int i = 0; i < storyEventsJsonList.size(); ++i) {
      nlohmann::json storyEventJson = storyEventsJsonList.at(i);
      result.push_back(StoryEventContent::getStoryEventFromJson(storyEventJson));
    }
  }
  return result;
}

StoryEventContent::StoryEventContent(const nlohmann::json &jsonContent)
{
  p_content = jsonContent;
  p_type = Utils::getStringFromJson(jsonContent, "type");
  p_comment = Utils::getStringFromJson(jsonContent, "__comment");
}

string StoryEventContent::getType() const
{
  return p_type;
}

string StoryEventContent::getComment() const
{
  return p_comment;
}

#include "MusicEventContent.hpp"
#include "WaitEventContent.hpp"
#include "PhotoEventContent.hpp"
#include "SubStoryEventContent.hpp"
#include "ConditionEventContent.hpp"
#include "ValueEventContent.hpp"
#include "StoryManager.hpp"
#include "PanelEventContent.hpp"
#include "DialogEventContent.hpp"
#include "SelectionEventContent.hpp"

StoryEventContent* StoryEventContent::getStoryEventFromJson(const nlohmann::json &jsonContent)
{
  CCASSERT(jsonContent.count("type"), ("Story Event type is required. json : " + jsonContent.dump()).c_str());
  string type = jsonContent.at("type");
  if (type == "music") {
    return new MusicEventContent(jsonContent);
  } else if (type == "wait") {
    return new WaitEventContent(jsonContent);
  } else if (type == "photo") {
    return new PhotoEventContent(jsonContent);
  } else if (type == "story") {
    return new SubStoryEventContent(jsonContent);
  } else if (type == "condition") {
    return new ConditionEventContent(jsonContent);
  } else if (type == "setValues") {
    return new ValueEventContent(jsonContent);
  } else if (type == "panel") {
    return new PanelEventContent(jsonContent);
  } else if (type == "dialog") {
    return new DialogEventContent(jsonContent);
  } else if (type == "selection") {
    return new SelectionEventContent(jsonContent);
  } else if (type == "popScene" || type == "stopStory" || type == "refreshScene" || type == "checkStory") {
  } else if (StoryManager::isFunctionRegistered(type)) {
  } else {
    CCLOGERROR("undefined story type : %s", type.c_str());
  }
  return new StoryEventContent(jsonContent);
}

#include "SceneManager.hpp"

void StoryEventContent::runEvent(StoryEventCallback callback)
{
  if (p_type == "popScene") {
    SceneManager::getShareInstance()->popScene();
  } else if (p_type == "stopStory") {
    StoryManager::getShareInstance()->stopStory();
  } else if (p_type == "refreshScene") {
    SceneManager::getShareInstance()->refreshScene();
  } else if (p_type == "checkStory") {
    StoryManager::getShareInstance()->checkAndStartStory();
    return;
  } else if (StoryManager::isFunctionRegistered(p_type)) {
    StoryManager::runFunction(p_type, p_content);
  }
  callback();
}
