//
//  StoryJsonData.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "StoryJsonData.hpp"
#include "StoryJsonContent.hpp"

StoryJsonData::~StoryJsonData()
{
  for (auto storyEvent : p_storyEventList) {
    delete storyEvent;
  }
  p_storyEventList.clear();
}

StoryJsonData* StoryJsonData::createStoryData(const string &jsonFileName)
{
  auto storyData = new StoryJsonData();
  storyData->initDataWithJson(jsonFileName);
  return storyData;
}

StoryJsonData* StoryJsonData::createStoryData(const nlohmann::json &jsonContent)
{
  auto storyData = new StoryJsonData();
  storyData->initDataWithJsonContent(jsonContent);
  return storyData;
}

void StoryJsonData::initDataWithJson(const std::string &jsonFileName)
{
  auto content = new StoryJsonContent(jsonFileName);
  p_sceneName = content->getScene();
  p_storyEventList = content->getStoryEventList();
  delete content;
}

void StoryJsonData::initDataWithJsonContent(const nlohmann::json &jsonContent)
{
  auto content = new StoryJsonContent(jsonContent);
  p_sceneName = content->getScene();
  p_storyEventList = content->getStoryEventList();
  delete content;
}

string StoryJsonData::getSceneName() const
{
  return p_sceneName;
}

vector<StoryEventContent *> StoryJsonData::getStoryEventsList() const
{
  return p_storyEventList;
}
