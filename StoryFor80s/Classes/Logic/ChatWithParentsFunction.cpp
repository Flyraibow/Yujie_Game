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


void startChat(ParentChatData *parentChat)
{
  parentChat->setExperienced(true);
  GameData::getSharedInstance()->setHasTalkedToParent(true);
  StoryManager::getShareInstance()->startStory(parentChat->getStory());
}

void story::chatWithParents(const nlohmann::json &jsonContent)
{
  // 如果已经聊过了就提示下次再说吧。
  // 如果有预定义的类，那么就执行预定义的剧情，没有的话出现正常的选项剧情。
  vector<pair<ParentChatData *, int>> possiblelist;
  int priority = 0;
  auto parentsChats = *ParentChatData::getSharedDictionary();
  for (auto parentChatPair : parentsChats) {
    auto parentChat = parentChatPair.second;
    if (!parentChat->getRepeat() && parentChat->getExperienced()) {
      continue;
    }
    // 起始时间要求不符合
    auto date = GameData::getSharedInstance()->getGameDateData();
    if (parentChat->getStartYear() > 0) {
      if (date->getYear() < parentChat->getStartYear()) {
        continue;
      } else if (date->getYear() == parentChat->getStartYear()) {
        if (parentChat->getStartMonth() > 0) {
          if (date->getMonth() < parentChat->getStartMonth()) {
            continue;
          }
        }
      }
    }
    // 结束时间要求不符合
    if (parentChat->getEndYear() > 0) {
      if (date->getYear() > parentChat->getEndYear()) {
        continue;
      } else if (date->getYear() == parentChat->getEndYear()) {
        if (parentChat->getEndMonth() > 0) {
          if (date->getMonth() > parentChat->getEndMonth()) {
            continue;
          }
        }
      }
    }
    if (!Manager::checkConditionByString(parentChat->getCondition())) {
      continue;
    }
    // 优先级 大于 1000 表示强制执行
    if (parentChat->getPriority() >= 1000) {
      startChat(parentChat);
      return;
    } else {
      priority += parentChat->getPriority();
      possiblelist.push_back(make_pair(parentChat, priority));
    }
  }
  if (priority > 0) {
    auto random = arc4random() % priority;
    for (auto chatPair : possiblelist) {
      if (chatPair.second > random) {
        startChat(chatPair.first);
        return;
      }
    }
  }
}
