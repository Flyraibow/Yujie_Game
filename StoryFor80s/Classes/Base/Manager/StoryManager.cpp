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
#include "EventManager.hpp"
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
  auto storyEventJson = story->getStoryEvent();
  auto storyJsonData = StoryJsonData::createStoryData(storyEventJson);
  
  if (storyJsonData != nullptr) {
    auto sceneName = storyJsonData->getSceneName();
    if (sceneName.length() > 0) {
      p_storyScene = BaseScene::createScene(sceneName);
      SceneManager::getShareInstance()->pushScene(p_storyScene);
    } else {
      p_storyScene = SceneManager::getShareInstance()->currentScene();
    }
    startStoryEventList(storyJsonData->getStoryEventsList());
  }
}

void StoryManager::checkAndStartStory()
{
  CCLOG("check stories");
  auto storyList = StoryData::getSharedDictionary();
  for (auto iter = storyList->begin(); iter != storyList->end(); iter++) {
    auto storyData = iter->second;
    if (storyData != nullptr) {
      if (!storyData->getOnce() || storyData->getCount() == 0) {
        if (DataManager::getShareInstance()->checkCondition(storyData->getConditionId())) {
          storyData->setCount(storyData->getCount() + 1);
          startStory(storyData);
        }
      }
      return;
    }
  }
}

void StoryManager::startStoryEventList(const vector<StoryEventContent *> &storyEventList)
{
  for (int i = (int)storyEventList.size() - 1; i >= 0; --i) {
    auto storyEvent = storyEventList.at(i);
    p_stackStories.push(storyEvent);
  }
  startNextStoryEvent();
}

void StoryManager::startNextStoryEvent()
{
  if (p_stackStories.size() > 0) {
    auto story = p_stackStories.top();
    p_stackStories.pop();
    startStoryEvent(story);
  } else {
    //    SceneManager::getShareInstance()->popScene();
    //    auto topScene = SceneManager::getShareInstance()->currentScene();
    //    topScene->refreshMusic();
    //    if (p_callback != nullptr) {
    //      p_callback();
    //    }
  }
}

void StoryManager::startStoryEvent(const StoryEventContent *storyEventContent)
{
  CCLOG("start story event: %s, comment : %s", storyEventContent->getType().c_str(), storyEventContent->getComment().c_str());
  storyEventContent->runEvent(p_storyScene, [this]() {
    this->startNextStoryEvent();
  });
//  auto type = storyEventData->getType();
//  auto paramters = storyEventData->getParametrsMap();
//  CCLOG("start story event: %s", storyEventData->description().c_str());
//  if (type == "stopMusic") {
//    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//  } else if (type == "playMusic") {
//    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
//    audioEngine->stopBackgroundMusic();
//    audioEngine->playBackgroundMusic(getPathFromMap(paramters).c_str(), true);
//  } else if (type == "playSound") {
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getPathFromMap(paramters).c_str());
//  } else if (type == "addPicture") {
////    addPictures(storyEventData);
//  } else if (type == "movePicture") {
////    movePictures(storyEventData);
//  } else if (type == "removePicture") {
////    auto name = storyEventData->getName();
////    p_originalValue.erase(name);
////    if (p_pictures.count(name)) {
////      auto picture = p_pictures.at(name);
////      picture->removeFromParent();
////      p_pictures.erase(name);
////    }
//  } else if (type == "dialog") {
////    if (!p_moveFast) {
////      addDialogs(storyData);
////      return;
////    }
//  } else if (type == "selection") {
////    showSelections(storyData);
////    return;
//  } else if (type == "data") {
////    auto parameters = storyData->getParametrsMap();
////    if (parameters.count("on")) {
////      auto addOnSwitches = Utils::split(parameters.at("on"), ',');
////      for (auto addOnSwitch : addOnSwitches) {
////        DataManager::getShareInstance()->setGameSwitch(addOnSwitch, true);
////      }
////    }
////    if (parameters.count("off")) {
////      auto addOnSwitches = Utils::split(parameters.at("off"), ',');
////      for (auto addOnSwitch : addOnSwitches) {
////        DataManager::getShareInstance()->setGameSwitch(addOnSwitch, false);
////      }
////    }
//  } else if (type == "subStory") {
////    auto parameters = storyData->getParametrsMap();
////    for (auto parameter : parameters) {
////      DataManager::getShareInstance()->setTempString(parameter.first, parameter.second);
////    }
////    if (storyData->getNextStoryData() != nullptr) {
////      p_stackStories.push(storyData->getNextStoryData());
////    }
////    auto subStory = StoryEventData::getStoryEventDataById(storyData->getName());
////    startStoryEvent(subStory);
////    return;
//  }
////  if (storyData->getDuration() > 0) {
////    if (p_storyEventDeltas.size() == 0) {
////      scheduleUpdate();
////    }
////    p_storyEventDeltas[storyData] = storyData->getDuration();
////  }
//  if (type == "wait") {
//    return;
//  } else {
//    startNextStoryEvent(storyEventData);
//  }
}

