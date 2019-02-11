//
//  EventManager.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#include "EventManager.hpp"

//#include "EventData.hpp"
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
//  eventName = DataManager::getShareInstance()->decipherString(eventName);
//  auto eventData = EventData::getEventDataById(eventName);
//  if (eventData == nullptr) {
//    CCLOGWARN("Counldn't find event : %s", eventName.c_str());
//    return;
//  }
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
