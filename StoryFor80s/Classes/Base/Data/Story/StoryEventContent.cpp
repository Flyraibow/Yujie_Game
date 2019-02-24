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

StoryEventContent* StoryEventContent::getStoryEventFromJson(const nlohmann::json &jsonContent)
{
  CCASSERT(jsonContent.count("type"), ("Story Event type is required. json : " + jsonContent.dump()).c_str());
  string type = jsonContent.at("type");
  if (type == "music") {
    return new MusicEventContent(jsonContent);
  } else if (type == "wait") {
    return new WaitEventContent(jsonContent);
  } else {
    CCASSERT(false, ("unsupported type" + type).c_str());
  }
  return new StoryEventContent(jsonContent);
}
