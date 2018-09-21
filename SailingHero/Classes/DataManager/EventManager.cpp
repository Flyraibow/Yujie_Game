//
//  EventManager.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/18/18.
//

#include "EventManager.hpp"
#include "EventData.hpp"
#include "SHScene.hpp"

EventManager* EventManager::p_sharedManager = nullptr;
SHScene* EventManager::p_currentScene = nullptr;

EventManager* EventManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new EventManager();
  }
  return p_sharedManager;
}


void EventManager::setCurrentScene(SHScene *scene)
{
  p_currentScene = scene;
}

#include "SystemButton.hpp"
#include "SceneManager.hpp"

void EventManager::runEvent(std::string eventName)
{
  if (eventName.size() == 0) return;
  auto eventData = EventData::getEventDataById(eventName);
  if (eventData == nullptr) {
    CCLOGWARN("Counldn't find event : %s", eventName.c_str());
    return;
  }
  CCLOG("start event : %s", eventName.c_str());
  auto eventType = eventData->getEventType();
  if (eventType == "groupButton") {
    CCASSERT(p_currentScene != nullptr, "current scene mustn't be nil");
    auto buttonGroup = SystemButton::getButtonGroupFromEvent(eventData->getParameters());
    p_currentScene->addChild(buttonGroup);
  } else if (eventType == "scene") {
    CCASSERT(eventData->getParameters().size() > 0, "scene must be provided with a name");
    SceneManager::getShareInstance()->pushScene(eventData->getParameters().at(0));
  } else {
    CCLOGWARN("unkown type event : %s, type : %s", eventName.c_str(), eventType.c_str());
  }
}
