//
//  MusicEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "MusicEventContent.hpp"
#include "JsonUtil.hpp"

#include "audio/include/SimpleAudioEngine.h"
#include <unordered_map>

MusicEventContent::MusicEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_path = Utils::getStringFromJson(jsonContent, "path");
  auto action = Utils::getStringFromJson(jsonContent, "action");
  static const unordered_map<string, MusicEventAction> actionMap = {
    {"stop", MusicEventActionStop},
    {"playMusic", MusicEventActionPlayBackgroundMusic},
    {"playEffect", MusicEventActionPlayEffect}
  };
  CCASSERT(actionMap.count(action), "unknown music story action");
  p_action = actionMap.at(action);
}

void MusicEventContent::runEvent(StoryEventCallback callback)
{
  switch (p_action) {
    case MusicEventActionStop:
      CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
      break;
    case MusicEventActionPlayBackgroundMusic:
      CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
      CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(p_path.c_str());
      break;
    case MusicEventActionPlayEffect:
      CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(p_path.c_str());
      break;
  }
  callback();
}
