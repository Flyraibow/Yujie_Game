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
  if (p_subStoryData == nullptr && p_subStoryName.length() > 0) {
    p_subStoryData = StoryJsonData::createStoryData(p_subStoryName);
  }
}

void SubStoryEventContent::runEvent(StoryEventCallback callback)
{
  if (p_subStoryData != nullptr) {
    StoryManager::getShareInstance()->startStory(p_subStoryData);
  } else {
    CCASSERT(false, "undefined sub story");
  }
  callback();
}

SubStoryEventContent::~SubStoryEventContent()
{
  if (p_subStoryData != nullptr) {
    delete p_subStoryData;
    p_subStoryData = nullptr;
  }
}
