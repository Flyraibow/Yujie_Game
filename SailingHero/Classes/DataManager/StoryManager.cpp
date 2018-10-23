//
//  StoryManager.cpp
//  SailingHero
//
//  Created by Yujie Liu on 10/19/18.
//

#include "StoryManager.hpp"
#include "StoryData.hpp"
#include "StoryEventData.hpp"
#include "GameData.hpp"
#include "SceneManager.hpp"
#include "StoryScene.hpp"

StoryManager* StoryManager::p_sharedManager = nullptr;

StoryManager* StoryManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new StoryManager();
  }
  return p_sharedManager;
}

void StoryManager::startStory(const StoryData *story)
{
  CCLOG("start story: %s", story->getStoryId().c_str());
  auto storyEvent = StoryEventData::getStoryEventDataById(story->getStoryEventId());
  if (storyEvent != nullptr) {
    p_storyScene = StoryScene::createScene();
    Director::getInstance()->pushScene(p_storyScene);
    p_storyScene->startStoryEvent(storyEvent);
  }
}

void StoryManager::checkAndStartStory()
{
  CCLOG("check stories");
  auto storyList = StoryData::getSharedDictionary();
  for (auto iter = storyList->begin(); iter != storyList->end(); iter++) {
    auto storyData = iter->second;
    
    if (storyData != nullptr) {
      auto gameData = GameData::getSharedInstance();
      if (storyData->getHeroData() != nullptr) {
        if (storyData->getHeroData() != gameData->getGuildData()->getLeaderData()) {
          continue;
        }
      }
      if (!storyData->getRepeated()) {
        if (gameData->getExperiencedStoriesDataSet().count(storyData)) {
          continue;
        }
      }
      startStory(storyData);
    }
  }
}
