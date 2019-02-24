//
//  SubStoryEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "SubStoryEventContent.hpp"
#include "JsonUtil.hpp"
#include "StoryManager.hpp"
#include "StoryJsonData.hpp"

SubStoryEventContent::SubStoryEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_subStoryName = Utils::getStringFromJson(jsonContent, "name");
  p_subStoryData = jsonContent.count("story") ? StoryJsonData::createStoryData(jsonContent.at("story")) : nullptr;
}

void SubStoryEventContent::runEvent(BaseScene *baseScene, StoryEventCallback callback)
{
  if (p_subStoryData != nullptr) {
    StoryManager::getShareInstance()->startStory(p_subStoryData);
  } else if (p_subStoryName.length() > 0) {
    StoryManager::getShareInstance()->startStory(p_subStoryName);
  } else {
    CCASSERT(false, "undefined sub story");
  }
  callback();
}

SubStoryEventContent::~SubStoryEventContent()
{
  if (p_subStoryData != nullptr) {
    delete p_subStoryData;
  }
}
