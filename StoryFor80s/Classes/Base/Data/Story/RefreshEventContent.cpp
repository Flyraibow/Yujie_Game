//
//  RefreshEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/23/19.
//

#include "RefreshEventContent.hpp"
#include "JsonUtil.hpp"
#include "BaseScene.hpp"
#include "SceneManager.hpp"


RefreshEventContent::RefreshEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_refreshIds = Utils::getStringListFromJson(jsonContent, "refresh_ids");
}

void RefreshEventContent::runEvent(StoryEventCallback callback)
{
  auto scene = SceneManager::getShareInstance()->currentScene();
  for (auto componentId : p_refreshIds) {
    scene->refreshComponentById(componentId);
  }
  callback();
}
