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
#include "DataManager.hpp"
#include "EventManager.hpp"

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
    SceneManager::getShareInstance()->pushScene(p_storyScene);
    p_storyScene->startStory(storyEvent, [this]() {
      this->startEventAfterComplete();
    });
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
      if (storyData->getCityData() != nullptr) {
        if (gameData->getCityData() != storyData->getCityData()) {
          continue;
        }
      }
      if (storyData->getBuildingData() != nullptr) {
        if (storyData->getBuildingData() != DataManager::getShareInstance()->getTempData<CityBuildingData>("building")) {
          continue;
        }
      }
      if (!storyData->getRepeated()) {
        if (gameData->getExperiencedStoriesDataSet().count(storyData)) {
          continue;
        }
      }
      auto experiencedStoriedIdSet = gameData->getExperiencedStoriesIdSet();
      experiencedStoriedIdSet.insert(storyData->getId());
      gameData->setExperiencedStoriesIdSet(experiencedStoriedIdSet);
      startStory(storyData);
      return;
    }
  }
  startEventAfterComplete();
}

void StoryManager::startEventAfterComplete() const
{
  auto eventId = DataManager::getShareInstance()->getTempString("event");
  EventManager::getShareInstance()->runEvent(eventId);
}
