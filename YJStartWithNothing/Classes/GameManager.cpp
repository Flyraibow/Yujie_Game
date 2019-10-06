//
//  GameManager.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#include "GameManager.hpp"
#include "BackgroundContainer.hpp"
#include "FrontContainer.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"
#include "EventData.hpp"
#include "QuickAlert.hpp"

GameManager* GameManager::p_manager = nullptr;

GameManager* GameManager::getInstance()
{
  if (p_manager == nullptr) {
    p_manager = new GameManager();
  }
  return p_manager;
}

void GameManager::setContainers(BackgroundContainer* back, FrontContainer* font)
{
  p_background = back;
  p_front = font;
  p_moving = false;
  p_started = false;
  p_timer = 0;
  p_values.clear();
  p_gradualValues.clear();
  loadEvents();
}

void GameManager::loadEvents()
{
  for (auto eventData: p_events) {
    delete eventData;
  }
  p_events.clear();
  p_eventsMap.clear();
  auto path = "data/events.json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  auto eventsList = JsonUtils::getJsonListFromJson(jsonContent, "events");
  
  for (auto event : eventsList) {
    auto eventData = new EventData(event);
    p_events.push_back(eventData);
  }
}

void GameManager::setMoving(bool flag)
{
  p_moving = flag;
  p_background->setMoving(flag);
}

void GameManager::setStarted(bool flag)
{
  p_started = flag;
}

double GameManager::getAge() const
{
  return p_timer / SECS_PER_YEAR;
}

void GameManager::update(double delta)
{
  double pAge = getAge();
  p_timer += delta;
  double cAge = getAge();
  
  if (cAge >= 1.0) {
    if (pAge < 1.0) {
      p_front->initAge();
    }
    p_front->updateAge();
  }
  
  for (auto event : p_events) {
    if (event->isNotStarted() && event->passCondition() && event->getAge() <= cAge) {
      p_background->addEvent(event);
    }
  }
  for (int i = (int)p_gradualValues.size() - 1; i >= 0; --i) {
    auto changeForType = p_gradualValues[i];
    auto type = changeForType.first;
    auto speed = changeForType.second.first;
    if (speed < 0) {
      ;
    }
    auto deltaAge = (cAge - pAge);
    auto length = changeForType.second.second - deltaAge;
    if (length < 0) {
      deltaAge = changeForType.second.second;
      p_gradualValues.erase(p_gradualValues.begin() + i);
    } else {
      p_gradualValues[i].second.second = length;
    }
    auto delta = speed * deltaAge;
    _changeValues(type, delta, false);
  }
}


void GameManager::_changeValues(string type, double deltaVal, bool showMsg)
{
  double originV = 0;
  if (p_values.count(type)) {
    originV = p_values.at(type);
  }
  auto value = originV + deltaVal;
  if (value < 0) {
    value = 0;
  }
  p_front->setValue(type, value);
  p_values[type] = value;
  
  if (showMsg) {
    if (deltaVal > 0) {
      auto val = to_string_with_precision<double>(deltaVal, 1);
      auto vStr = type + " + " + val;
      QuickAlert::createAlertWithMsg(vStr, Color4B::GREEN);
    } else if (deltaVal < 0) {
      auto val = to_string_with_precision<double>(deltaVal, 1);
      auto vStr = type + " " + val;
      QuickAlert::createAlertWithMsg(vStr, Color4B::RED);
    }
  }

}


void GameManager::valueChange(ValueChangeData* valueChange)
{
  if (valueChange->isInstant()) {
    _changeValues(valueChange->getType(), valueChange->getValue(), true);
  } else {
    if (valueChange->getValue() < 0) {
      ;
    }
    pair<double, double> change = make_pair(valueChange->getValue(), valueChange->getLength());
    pair<string, pair<double, double>> changeForType = make_pair(valueChange->getType(), change);
    p_gradualValues.push_back(changeForType);
  }
}

void GameManager::removeEvent(EventData* eventData)
{
  for (int i = (int)p_events.size() - 1; i >= 0; --i) {
    if (eventData == p_events.at(i)) {
      p_events.erase(p_events.begin() + i);
    }
  }
}

double GameManager::getTypeValue(const string &type) const
{
  if (p_values.count(type)) {
    return p_values.at(type);
  }
  return 0;
}
