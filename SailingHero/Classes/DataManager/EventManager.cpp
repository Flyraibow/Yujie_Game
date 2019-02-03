//
//  EventManager.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/18/18.
//

#include "EventManager.hpp"
#include "EventData.hpp"
#include "SHScene.hpp"
#include "Utils.hpp"
#include "SHDataManager.hpp"
#include "SHGlobalDataManager.hpp"

EventManager* EventManager::p_sharedManager = nullptr;
SHScene* EventManager::p_currentScene = nullptr;

EventManager* EventManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new EventManager();
  }
  return p_sharedManager;
}

EventManager::EventManager()
{
  p_groupButton = nullptr;
}

void EventManager::setCurrentScene(SHScene *scene)
{
  p_currentScene = scene;
}

#include "SystemButton.hpp"
#include "SceneManager.hpp"
#include "DataManager.hpp"
#include "StoryManager.hpp"

void EventManager::runEvent(std::string eventName)
{
  if (eventName.size() == 0) return;
  eventName = DataManager::getShareInstance()->decipherString(eventName);
  auto eventData = EventData::getEventDataById(eventName);
  if (eventData == nullptr) {
    CCLOGWARN("Counldn't find event : %s", eventName.c_str());
    return;
  }
  CCLOG("start event : %s", eventName.c_str());
  auto eventType = eventData->getEventType();
  if (eventType == "groupButton") {
    CCASSERT(p_currentScene != nullptr, "current scene mustn't be nil");
    vector<string> selections;
    if (eventData->getParameters().size() > 1) {
      selections = eventData->getParameters();
    } else {
      auto selectionStr = DataManager::getShareInstance()->decipherString(eventData->getParameters().at(0));
      selections = SHUtil::atovector(selectionStr);
    }
    if (selections.size() > 0) {
      if (p_groupButton != nullptr) {
        p_groupButton->removeFromParent();
        p_groupButton = nullptr;
      }
      p_groupButton = SystemButton::getButtonGroupFromEvent(selections);
      p_currentScene->addChild(p_groupButton, 1000);
    }
  } else if (eventType == "removeGroupButton") {
    if (p_groupButton != nullptr) {
      p_groupButton->removeFromParent();
      p_groupButton = nullptr;
    }
  } else if (eventType == "scene") {
    CCASSERT(eventData->getParameters().size() > 0, "scene must be provided with a name");
    SceneManager::getShareInstance()->pushScene(eventData->getParameters().at(0));
  } else if (eventType == "setScene") {
    CCASSERT(eventData->getParameters().size() > 0, "scene must be provided with a name");
    SceneManager::getShareInstance()->pushScene(eventData->getParameters().at(0));
  } else if (eventType == "popScene") {
    SceneManager::getShareInstance()->popScene();
  } else if (eventType == "panel") {
    CCASSERT(eventData->getParameters().size() > 0, "panel must be provided with a name");
    SceneManager::getShareInstance()->addPanel(eventData->getParameters().at(0));
  } else if (eventType == "popPanel") {
    SceneManager::getShareInstance()->popPanel();
  } else if (eventType == "storyCheck") {
    StoryManager::getShareInstance()->checkAndStartStory();
  } else if (eventType == "eventList") {
    for (int i = 0; i < eventData->getParameters().size(); ++i) {
      runEvent(eventData->getParameters().at(i));
    }
  } else if (eventType == "setTempStr") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 2, "setTempStr must be provided with key and value");
    DataManager::getShareInstance()->setTempString(parameters.at(0), parameters.at(1));
  } else if (eventType == "processPanel") {
    auto panel = SceneManager::getShareInstance()->topPanel();
    panel->process();
  } else if (eventType == "setDataValue") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 3, "setDataValue must be provided with key, field and value");
    DataManager::getShareInstance()->setDataValue(parameters.at(0), parameters.at(1), parameters.at(2));
  } else if (eventType == "refreshScene") {
    SceneManager::getShareInstance()->refreshScene();
  } else if (eventType == "condition") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 3, "condition must be provided with conditionId, successEvent and failureEvent");
    if (DataManager::getShareInstance()->checkCondition(parameters.at(0))) {
      runEvent(parameters.at(1));
    } else {
      runEvent(parameters.at(2));
    }
  } else if (eventType == "dialog") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() > 0, "dialog must be provided with dialogId");
    SceneManager::getShareInstance()->addDialog(parameters);
  } else if (eventType == "saveData") {
    // save game
    auto indexString = DataManager::getShareInstance()->decipherString("temp.index");
    SHDataManager::saveData(indexString);
    SHGlobalDataManager::saveData("");
  } else if (eventType == "loadData") {
    // load game
    auto indexString = DataManager::getShareInstance()->decipherString("temp.index");
    SHDataManager::loadData(indexString);
    
  } else if (eventType == "setTempData") {
    auto parameters = eventData->getParameters();
    if (parameters.size() == 3) {
      DataManager::getShareInstance()->setData(parameters.at(0), parameters.at(1), parameters.at(2));
    } else if (parameters.size() == 2) {
      auto data = DataManager::getShareInstance()->decipherData(parameters.at(1));
      DataManager::getShareInstance()->setTempData(parameters.at(0), data);
    } else {
      CCASSERT(false, "setTempData must be provided with key, data name and value, or key and value");
    }
  } else if (eventType == "setTempDataList") {
    auto parameters = eventData->getParameters();
    if (parameters.size() == 3) {
      DataManager::getShareInstance()->setDataList(parameters.at(0), parameters.at(1), parameters.at(2));
    } else if (parameters.size() == 4) {
      DataManager::getShareInstance()->setDataList(parameters.at(0), parameters.at(1), parameters.at(2), parameters.at(3));
    } else {
      CCASSERT(false, "setTempDataList must be provided with key, data name and value, or key, data name, list, list key");
    }
  } else if (eventType == "filtTempDataList") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 3, "filtTempDataList must be provided with key, tempKey name and condiiton");
    DataManager::getShareInstance()->filtDataList(parameters.at(0), parameters.at(1), parameters.at(2));
  } else if (eventType == "setSortTempKeyValuePair") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 4, "setSortTempKeyValuePair must be provided with key, type, content and compare condiiton");
    DataManager::getShareInstance()->setSortKeyValuePair(parameters.at(0), parameters.at(1), parameters.at(2), parameters.at(3));
  } else {
    CCLOGWARN("unkown type event : %s, type : %s", eventName.c_str(), eventType.c_str());
  }
}
