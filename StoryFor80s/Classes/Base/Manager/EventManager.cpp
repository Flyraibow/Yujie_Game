//
//  EventManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#include "EventManager.hpp"

#include "EventData.hpp"
#include "DataManager.hpp"
#include "SceneManager.hpp"
#include "ConditionManager.hpp"
#include "Utils.hpp"

EventManager* EventManager::p_sharedManager = nullptr;
BaseScene* EventManager::p_currentScene = nullptr;

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

void EventManager::setCurrentScene(BaseScene *scene)
{
  p_currentScene = scene;
}

void EventManager::runEvent(std::string eventName)
{
  if (eventName.size() == 0) return;
  eventName = DataManager::getShareInstance()->decipherString(eventName);
  auto eventData = EventData::getEventDataById(eventName);
  if (eventData == nullptr) {
    CCLOGWARN("Counldn't find event : %s", eventName.c_str());
    return;
  }
  auto eventType = eventData->getType();
  auto parameters = eventData->getParametrsMap();
  if (eventType == "pushScene") {
    if (parameters.count("sceneName")) {
      auto sceneName = DataManager::getShareInstance()->decipherString(parameters.at("sceneName"));
      SceneManager::getShareInstance()->pushScene(sceneName);
    }
  } else if (eventType == "popScene") {
    SceneManager::getShareInstance()->popScene();
  } else if (eventType == "condition") {
    auto conditionStr = parameters.count("condition") ? parameters.at("condition") : "";
    if (Manager::checkConditionByString(conditionStr)) {
      if (parameters.count("yes")) {
        p_eventStack.push(parameters.at("yes"));
      }
    } else if (parameters.count("no")) {
      p_eventStack.push(parameters.at("no"));
    }
  } else if (eventType == "eventlist") {
    auto eventStr = parameters.count("event") ? parameters.at("event") : "";
    auto events = SHUtil::split(eventStr, ',');
    for (int i = events.size() - 1; i >= 0; --i) {
      p_eventStack.push(events.at(i));
    }
  } else if (eventType == "setValues") {
    for (auto iter = parameters.begin(); iter != parameters.end(); ++iter) {
      auto key = iter->first;
      auto value = iter->second;
      DataManager::getShareInstance()->setValue(key, value);
    }
  } else {
    CCLOGWARN("unrecognized event type : %s", eventType.c_str());
  }
  continueEvent();
}


void EventManager::addGroupButton(const vector<string> &parameters)
{
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
