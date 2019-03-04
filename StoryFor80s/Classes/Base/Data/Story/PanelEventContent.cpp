//
//  PanelEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "PanelEventContent.hpp"
#include "JsonUtil.hpp"
#include "BaseScene.hpp"
#include "SceneManager.hpp"


PanelEventContent::PanelEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_name = Utils::getStringFromJson(jsonContent, "name");
  CCASSERT(p_name.length() > 0, "story panel event, name shouldn't be empty");
}

void PanelEventContent::runEvent(StoryEventCallback callback)
{
  SceneManager::getShareInstance()->addPanel(p_name);
}
