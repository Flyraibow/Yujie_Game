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
  p_seconds = 0;
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
#include "SHGameDataHelper.hpp"

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
    addGroupButton(eventData->getParameters());
  } else if (eventType == "removeGroupButton") {
    removeGroupButton();
  } else if (eventType == "removeDialog") {
    SceneManager::getShareInstance()->removeDialog();
  } else if (eventType == "wait") {
    p_seconds = eventData->getParameters().size() == 0.0 ? 1: atof(eventData->getParameters().at(0).c_str());
    // wait seconds
    p_currentScene->schedule([this] (float delay) {
      this->continueEvent();
    }, p_seconds, 1, 0, "wait");
    return;
  } else if (eventType == "passDay") {
    int days = eventData->getParameters().size() == 0.0 ? 1: atoi(eventData->getParameters().at(0).c_str());
    // wait days
    passDays(days);
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
    for (int i = (int)eventData->getParameters().size() - 1; i >= 0; --i) {
      p_eventStack.push(eventData->getParameters().at(i));
    }
  } else if (eventType == "setTempStr") {
    auto parameters = eventData->getParameters();
    if (parameters.size() == 2) {
      DataManager::getShareInstance()->setTempString(parameters.at(0), parameters.at(1));
    } else if (parameters.size() == 4) {
      DataManager::getShareInstance()->calculateTempString(parameters.at(0), parameters.at(1), parameters.at(2), parameters.at(3));
    } else {
      CCASSERT(false, "un-recognized set temp str.");
    }
  } else if (eventType == "processPanel") {
    auto panel = SceneManager::getShareInstance()->topPanel();
    panel->process();
  } else if (eventType == "setDataValue") {
    auto parameters = eventData->getParameters();
    if (parameters.size() == 3) {
      DataManager::getShareInstance()->setDataValue(parameters.at(0), parameters.at(1), parameters.at(2));
    } else if (parameters.size() == 5) {
      DataManager::getShareInstance()->setDataValue(parameters.at(0), parameters.at(1), parameters.at(2), parameters.at(3), parameters.at(4));
    } else {
      CCASSERT(false, "setDataValue must be provided with key, field and value or (key, field and type, func, value)");
    }
  } else if (eventType == "refreshScene") {
    SceneManager::getShareInstance()->refreshScene();
  } else if (eventType == "condition") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() == 3, "condition must be provided with conditionId, successEvent and failureEvent");
    if (DataManager::getShareInstance()->checkCondition(parameters.at(0))) {
      p_eventStack.push(parameters.at(1));
    } else {
      p_eventStack.push(parameters.at(2));
    }
  } else if (eventType == "dialog") {
    auto parameters = eventData->getParameters();
    CCASSERT(parameters.size() > 0, "dialog must be provided with dialogId");
    removeGroupButton();
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
  continueEvent();
}


void EventManager::addGroupButton(const vector<string> &parameters)
{
  CCASSERT(p_currentScene != nullptr, "current scene mustn't be nil");
  CCASSERT(parameters.size() > 0, "must contain at least one button.");
  removeGroupButton();
  if (SHUtil::split(parameters.at(0), ',').size() == 2) {
    // the format is string1,event1;string2,event2...
    vector<SHButton*> buttons;
    for (auto str : parameters) {
      auto arr = SHUtil::split(str, ',');
      if (arr.size() == 2) {
        auto text = DataManager::getShareInstance()->decipherString(arr[0]);
        auto eventId = DataManager::getShareInstance()->decipherString(arr[1]);
        auto button = SystemButton::defaultButtonWithText(text, [eventId, this](cocos2d::Ref* pSender) {
          this->runEvent(eventId);
        });
        buttons.push_back(button);
      }
    }
    p_groupButton = SystemButton::getButtonGroupNode(buttons);
  } else {
    vector<string> selections;
    if (parameters.size() > 1) {
      selections = parameters;
    } else {
      auto selectionStr = DataManager::getShareInstance()->decipherString(parameters.at(0));
      selections = SHUtil::atovector(selectionStr);
    }
    p_groupButton = SystemButton::getButtonGroupFromButtonData(selections);
  }
  p_currentScene->addChild(p_groupButton, 1000);
}

void EventManager::removeGroupButton()
{
  if (p_groupButton != nullptr) {
    p_groupButton->removeFromParent();
    p_groupButton = nullptr;
  }
}

void EventManager::continueEvent()
{
  if (!p_eventStack.empty()) {
    auto event_id = p_eventStack.top();
    p_eventStack.pop();
    runEvent(event_id);
  }
}
