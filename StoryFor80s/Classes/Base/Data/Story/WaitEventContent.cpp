//
//  WaitEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "WaitEventContent.hpp"
#include "JsonUtil.hpp"
#include "SceneManager.hpp"
#include "BaseColorNode.hpp"


WaitEventContent::WaitEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_duration = Utils::getFloatFromJson(jsonContent, "duration");
}

void WaitEventContent::runEvent(StoryEventCallback callback)
{
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  auto colorNode = BaseColorNode::create(Color4B(), baseScene->getContentSize().width, baseScene->getContentSize().height);
  baseScene->addChild(colorNode, SCREEN_FOREGROUND_LAYER_HEIGHT);
  baseScene->schedule([callback, colorNode] (float delta) {
    colorNode->removeFromParent();
    callback();
  }, p_duration, 0, 0, "story_wait");
}

