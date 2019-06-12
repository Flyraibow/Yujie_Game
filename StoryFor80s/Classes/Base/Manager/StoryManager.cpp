//
//  StoryManager.cpp
//  StoryFor80s-mobile
//
//  Created by Yujie Liu on 2/23/19.
//

#include "StoryManager.hpp"

#include "StoryData.hpp"
#include "GameData.hpp"
#include "SceneManager.hpp"
#include "BaseScene.hpp"
#include "DataManager.hpp"
#include "StoryJsonData.hpp"

string getPathFromMap(const map<string, string> &storyEventDataParamters)
{
  return storyEventDataParamters.count("path") ? storyEventDataParamters.at("path") : "";
}

float getDurationFromMap(const map<string, string> &storyEventDataParamters)
{
  return storyEventDataParamters.count("duration") ? atof(storyEventDataParamters.at("path").c_str()) : 0;
}

StoryManager* StoryManager::p_sharedManager = nullptr;
unordered_map<string, SpecialFunctionWithDict> StoryManager::s_specialEventMap = unordered_map<string, SpecialFunctionWithDict>();

StoryManager* StoryManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new StoryManager();
  }
  return p_sharedManager;
}

void StoryManager::registerSpecialEventFunction(const string &eventId, SpecialFunctionWithDict function)
{
  s_specialEventMap[eventId] = function;
}

bool StoryManager::isFunctionRegistered(const string &functionId)
{
  return s_specialEventMap.count(functionId);
}

void StoryManager::runFunction(const string &functionId, const nlohmann::json &jsonContent)
{
  CCASSERT(s_specialEventMap.count(functionId), ("special function not exist:" + functionId).c_str());
  s_specialEventMap.at(functionId)(jsonContent);
}

void StoryManager::startStory(const StoryData *story)
{
  startStory(story->getStoryEvent());
}

void StoryManager::checkAndStartStory()
{
  CCLOG("check stories");
  auto storyList = StoryData::getSharedDictionary();
  for (auto iter = storyList->begin(); iter != storyList->end(); iter++) {
    auto storyData = iter->second;
    if (storyData != nullptr) {
      if (storyData->getOnce() && storyData->getCount() > 0) {
        continue;
      }
      if (storyData->getYear() > 0 && storyData->getYear() != GameData::getSharedInstance()->getGameDateData()->getYear()) {
        continue;
      }
      if (storyData->getMonth() > 0 && storyData->getMonth() != GameData::getSharedInstance()->getGameDateData()->getMonth()) {
        continue;
      }
      if (!storyData->getOnce() || storyData->getCount() == 0) {
        storyData->setCount(storyData->getCount() + 1);
        startStory(storyData);
      }
      return;
    }
  }
}

void StoryManager::addStoryEventList(const vector<StoryEventContent *> &storyEventList)
{
  for (int i = (int)storyEventList.size() - 1; i >= 0; --i) {
    auto storyEvent = storyEventList.at(i);
    p_stackStories.push(storyEvent);
  }
}

void StoryManager::startNextStoryEvent()
{
  if (p_stackStories.size() > 0) {
    auto story = p_stackStories.top();
    p_stackStories.pop();
    startStoryEvent(story);
  } else {
    p_currentEvent = nullptr;
    //    SceneManager::getShareInstance()->popScene();
    //    auto topScene = SceneManager::getShareInstance()->currentScene();
    //    topScene->refreshMusic();
    //    if (p_callback != nullptr) {
    //      p_callback();
    //    }
  }
}

void StoryManager::startStoryEvent(StoryEventContent *storyEventContent)
{
  CCLOG("start story event: %s, comment : %s", storyEventContent->getType().c_str(), storyEventContent->getComment().c_str());
  storyEventContent->runEvent([this, storyEventContent]() {
    
    CCLOG("======= call back of start story event: %s, comment : %s", storyEventContent->getType().c_str(), storyEventContent->getComment().c_str());
    this->startNextStoryEvent();
  });
  p_currentEvent = storyEventContent;
}

bool StoryManager::startStory(const string &storyName)
{
  CCLOG("========== start story: %s", storyName.c_str());
  auto storyJsonData = StoryJsonData::createStoryData(storyName);
  return startStory(storyJsonData);
}

bool StoryManager::startStory(const StoryJsonData *storyJsonData)
{
  CCLOG("================= start new Story");
  if (storyJsonData != nullptr) {
    auto sceneName = storyJsonData->getSceneName();
    if (sceneName.length() > 0) {
      p_storyScene = BaseScene::createScene(sceneName);
      SceneManager::getShareInstance()->pushScene(p_storyScene);
    } else {
      p_storyScene = SceneManager::getShareInstance()->currentScene();
    }
    if (p_stackStories.size() == 0) {
      p_currentEvent = nullptr;
    }
    addStoryEventList(storyJsonData->getStoryEventsList());
    if (p_currentEvent == nullptr) {
      startNextStoryEvent();
      return true;
    }
  }
  return false;
}

void StoryManager::stopStory()
{
  p_stackStories = stack<StoryEventContent *>();
  p_currentEvent = nullptr;
}
