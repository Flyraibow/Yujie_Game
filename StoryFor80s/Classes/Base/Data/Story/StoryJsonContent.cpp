//
//  StoryJsonContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "StoryJsonContent.hpp"
#include "JsonUtil.hpp"

using namespace nlohmann;

StoryJsonContent::StoryJsonContent(const std::string &jsonFileName) : JSONContent("res/base/story/" + jsonFileName + ".json")
{
}

std::string StoryJsonContent::getScene() const
{
  return Utils::getStringFromJson(p_jsonContent, "scene");
}

vector<StoryEventContent *> StoryJsonContent::getStoryEventList() const
{
  return StoryEventContent::getStoryEventsFromJson(p_jsonContent);
}
