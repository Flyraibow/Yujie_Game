//
//  ChatWithParentsFunction.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/11/19.
//

#include "ChatWithParentsFunction.hpp"
#include "ParentChatData.hpp"
#include "ConditionManager.hpp"
#include "StoryManager.hpp"
#include "GameData.hpp"

void story::chatWithParents(const nlohmann::json &jsonContent)
{
  // 如果已经聊过了就提示下次再说吧。
  // 如果有预定义的类，那么就执行预定义的剧情，没有的话出现正常的选项剧情。
  auto parentsChats = *ParentChatData::getSharedDictionary();
  for (auto parentChatPair : parentsChats) {
    auto parentChat = parentChatPair.second;
    if (!parentChat->getRepeat() && parentChat->getExperienced()) {
      continue;
    }
    if (!Manager::checkConditionByString(parentChat->getCondition())) {
      continue;
    }
    parentChat->setExperienced(true);
    GameData::getSharedInstance()->setHasTalkedToParent(true);
    StoryManager::getShareInstance()->startStory(parentChat->getStory());
    return;
  }
}
