//
//  WaitEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "WaitEventContent.hpp"
#include "JsonUtil.hpp"
#include "BaseScene.hpp"


WaitEventContent::WaitEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_duration = Utils::getFloatFromJson(jsonContent, "duration");
}

void WaitEventContent::runEvent(BaseScene *baseScene, StoryEventCallback callback) const
{
  baseScene->schedule([callback] (float delta) {
    callback();
  }, p_duration, 0, 0, "story_wait");
}
