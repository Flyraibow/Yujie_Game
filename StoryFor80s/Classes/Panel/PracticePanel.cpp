//
//  PracticePanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#include "PracticePanel.hpp"
#include "MyScheduleData.hpp"
#include "ConditionManager.hpp"
#include "ScheduleTypeData.hpp"
#include "BaseButton.hpp"
#include "SelectableScheduleData.hpp"
#include "SpriteComponent.hpp"
#include "BaseSpriteListener.hpp"

#include "ui/UIScrollView.h"

void showMyScheduleOnLabel(const MyScheduleData *mySchedule, Label *label)
{
  if (!Manager::checkConditionByString(mySchedule->getCondition())) {
    // TODO: FIND somewhere else to define the
    auto lockedScheduleType = ScheduleTypeData::getScheduleTypeDataById("locked");
    label->setString(lockedScheduleType->getName());
  }
  string typeId = mySchedule->getTypeData()->getId();
  if (typeId == "sleep") {
    label->setString(mySchedule->getTypeData()->getName());
  } else {
    label->setString(mySchedule->getTypeData()->getName() + " " + mySchedule->getScheduleData()->getName());
  }
}

MyScheduleData* findNextEmptyMySchedule()
{
  for (int i = 1; i <= 5; ++i) {
    string index = to_string(i);
    auto mySchedule = MyScheduleData::getMyScheduleDataById(index);
    if (mySchedule->getTypeId() == "sleep") {
      return mySchedule;
    }
  }
  return nullptr;
}

const vector<SelectableScheduleData *> getFullBaseScheduleList(const string &type)
{
  static unordered_map<string, vector<SelectableScheduleData *>> baseDataListMap;
  if (baseDataListMap.count(type)) {
    return baseDataListMap.at(type);
  }
  vector<SelectableScheduleData *> baseDataList;
  auto selectableScheduleMap = *SelectableScheduleData::getSharedDictionary();
  for (auto dataPair : selectableScheduleMap) {
    if (dataPair.second->getTypeId() == type) {
      baseDataList.push_back(dataPair.second);
    }
  }
  baseDataListMap[type] = baseDataList;
  return baseDataList;
}


// TODO: think about how to combine all these function into one
// 1. Add an abstract class for it.
vector<SelectableScheduleData *> getScheduleDataList(const string &type, const string &subtypeFilter = "")
{
  vector<SelectableScheduleData *> baseDataList = getFullBaseScheduleList(type);
  vector<SelectableScheduleData *> results;
  for (auto baseData : baseDataList) {
    auto condition = baseData->getCondition();
    if (!Manager::checkConditionByString(condition)) {
      continue;
    }
    if (subtypeFilter.length() > 0) {
      auto subTypeId = baseData->getSubTypeId();
      if (subTypeId != subtypeFilter) {
        continue;
      }
    }
    results.push_back(baseData);
  }
  return results;
}

BasePanel* PracticePanel::createPanel()
{
  return new PracticePanel();
}

PracticePanel::PracticePanel() : BasePanel("practicePanel")
{
}

void PracticePanel::initialize()
{
  vector<Label *> practicingLabels;
  for (int i = 1; i <= 5; ++i) {
    string index = to_string(i);
    auto label = getComponentById<Label>("practice_selected_lab_" + index);
    auto sprite = getComponentById<Label>("practice_selected_" + index);
    auto listener = BaseSpriteListener::createWithNode(sprite, false);
    listener->setTouchEnd(CC_CALLBACK_2(PracticePanel::unSelectSchedule, this), nullptr);
    practicingLabels.push_back(label);
    auto mySchedule = MyScheduleData::getMyScheduleDataById(index);
    showMyScheduleOnLabel(mySchedule, label);
  }
  for (auto typePair : *ScheduleTypeData::getSharedDictionary()) {
    if (typePair.second->getSelectable()) {
      auto button = getComponentById<BaseButton>(typePair.first);
      if (button != nullptr) {
        button->setClickEventListener([this](cocos2d::Ref *pSender) {
          auto btn = dynamic_cast<BaseButton*>(pSender);
          this->selectScheduleType(btn->getName());
        });
      }
    }
  }
  selectScheduleType("selfStudy");
}

void PracticePanel::selectScheduleType(const string &type)
{
  auto btn = getComponentById<BaseButton>(type);
  auto previous =  getComponentById<BaseButton>(p_selectedType);
  if (previous == btn) {
    btn->setHighlighted(true);
    return;
  }
  p_selectedType = type;
  if (previous != nullptr) {
    previous->setHighlighted(false);
  }
  btn->setHighlighted(true);
  auto scheduleList = getScheduleDataList(type, "");
  for (int i = (int)p_selectableComponents.size() - 1; i > 0; --i) {
    delete p_selectableComponents[i];
  }
  p_selectableComponents.clear();
  p_selectableSpriteComponents.clear();
  int i = 0;
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  for (auto schedule : scheduleList) {
    CCLOG("selectable: %s", schedule->getName().c_str());
    auto component = generateSelecatableSpriteComponent(schedule);
    p_selectableComponents.push_back(component);
    auto sprite = component->getNode();
    auto listener = BaseSpriteListener::createWithNode(sprite, false);
    listener->setTouchEnd(CC_CALLBACK_2(PracticePanel::selectSchedule, this), nullptr);
    sprite->setPosition(Vec2(0, i * 61));
    component->refresh();
    scrollView->addChild(sprite);
    ++i;
  }
  
  scrollView->setInnerContainerSize(Size(600, 61 * p_selectableSpriteComponents.size()));
}

SpriteComponent* PracticePanel::generateSelecatableSpriteComponent(SelectableScheduleData *selectableData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("selectablePracticeSprite"));
  component->setId(selectableData->getId());
  component->addComponentToParent(p_selectableSpriteComponents);
  component->setAssociateData(selectableData);
  auto labelComponent = component->getChildComponentById("selectable_lab");
  labelComponent->setAssociateData(selectableData);
  return component;
}

void PracticePanel::selectSchedule(Touch* touch, Event* event)
{
  auto sprite = event->getCurrentTarget();
  CCLOG("click : %s", sprite->getName().c_str());
  if (p_selectableSpriteComponents.count(sprite->getName())) {
    auto mySchedule = findNextEmptyMySchedule();
    if (mySchedule != nullptr) {
      auto component = p_selectableSpriteComponents.at(sprite->getName());
      auto selectableSchedule = dynamic_cast<SelectableScheduleData *>(component->getAssociateData());
      mySchedule->setTypeId(selectableSchedule->getTypeId());
      mySchedule->setScheduleId(selectableSchedule->getId());
      auto label = getComponentById<Label>("practice_selected_lab_" + mySchedule->getId());
      showMyScheduleOnLabel(mySchedule, label);
    }
  } else {
    CCLOGWARN("sprite Not exist : %s", sprite->getName().c_str());
  }
}

void PracticePanel::unSelectSchedule(Touch* touch, Event* event)
{
  auto sprite = event->getCurrentTarget();
  auto spriteName = sprite->getName();
  CCLOG("unselect schedule : %s", spriteName.c_str());
  char c = spriteName.at(spriteName.length() - 1);;
  string unselectIndex(1, c);
  auto mySchedule = MyScheduleData::getMyScheduleDataById(unselectIndex);
  if (mySchedule->getId() != "sleep") {
    mySchedule->setTypeId("sleep");
    mySchedule->setScheduleId("");
    auto label = getComponentById<Label>("practice_selected_lab_" + mySchedule->getId());
    showMyScheduleOnLabel(mySchedule, label);
  }
}
