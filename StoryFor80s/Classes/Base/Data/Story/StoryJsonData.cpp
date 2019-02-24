//
//  StoryJsonData.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "StoryJsonData.hpp"
#include "StoryJsonContent.hpp"

StoryJsonData* StoryJsonData::createStoryData(const string &jsonFileName)
{
  auto storyData = StoryJsonData::create();
  storyData->initDataWithJson(jsonFileName);
  return storyData;
}

void StoryJsonData::initDataWithJson(const std::string &jsonFileName)
{
  auto content = new StoryJsonContent(jsonFileName);
  p_sceneName = content->getScene();
  p_storyEventList = content->getStoryEventList();
  delete content;
}

string StoryJsonData::getSceneName() const
{
  return p_sceneName;
}

vector<StoryEventContent *> StoryJsonData::getStoryEventsList()
{
  return p_storyEventList;
}
