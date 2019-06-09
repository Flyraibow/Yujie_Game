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
#include "ScheduleSubTypeData.hpp"
#include "BaseDropDownMenu.hpp"
#include "SceneManager.hpp"
#include "LocalizationHelper.hpp"

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
    auto scheduleData = mySchedule->getScheduleData();
    auto text = mySchedule->getTypeData()->getName() + " " + scheduleData->getName() + " ";
    auto proficiencyData = scheduleData->getProficiencyData();
    if (proficiencyData != nullptr) {
      text += scheduleData->getTypeData()->getProficienceWord() + ": ";
      text += to_string(proficiencyData->getValue()) + "/" + to_string(proficiencyData->getMaxValue());
    }
    label->setString(text);
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
  // initial filterBar
  auto filterSprite = getComponentById<Sprite>("filter");
  auto listener = BaseSpriteListener::createWithNode(filterSprite, false);
  listener->setTouchEnd(CC_CALLBACK_2(PracticePanel::clickFilterBar, this), nullptr);
  selectScheduleType("selfStudy");
}

void PracticePanel::clickFilterBar(Touch* touch, Event* event)
{
  auto subtypeMap = *ScheduleSubTypeData::getSharedDictionary();
  vector<string> results;
  vector<string> labels;
  results.push_back("");
  labels.push_back(LocalizationHelper::getLocalization("empty"));
  for (auto subtypePair : subtypeMap) {
    if (subtypePair.second->getScheduleTypeId() == p_selectedType) {
      results.push_back(subtypePair.first);
      labels.push_back(subtypePair.second->getName());
    }
  }
  auto dropDown = BaseDropDownMenu::create([this, results](int index){
    if (index >= 0) {
      CCLOG("select sub type : %s", results.at(index).c_str());
      selectScheduleType(p_selectedType, results.at(index));
    } else {
      CCLOG("canceled");
    }
  });
  dropDown->setSelections(labels);
  dropDown->setMaxHeight(200);
  dropDown->setDropDownMenuItem(Size(200, 22), Color4B(100, 100, 100, 100), Color4B(200, 100, 100, 100));
  dropDown->render();
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  baseScene->addChild(dropDown, SCREEN_DIALOG_LAYER);
}

void PracticePanel::selectScheduleType(const string &type, const string &subtype)
{
  auto btn = getComponentById<BaseButton>(type);
  auto previous =  getComponentById<BaseButton>(p_selectedType);
  auto filterSubType = subtype;
  if (previous == btn) {
    btn->setHighlighted(true);
    if (p_selectedSubType == subtype) {
      return;
    }
  } else if (previous != nullptr) {
    previous->setHighlighted(false);
    if (subtype == "" && p_lastSubTypeFilter.count(type) && p_lastSubTypeFilter.at(type).length() > 0) {
      filterSubType = p_lastSubTypeFilter.at(type);
    }
  }
  p_selectedType = type;
  btn->setHighlighted(true);
  p_selectedSubType = filterSubType;
  p_lastSubTypeFilter[type] = filterSubType;
  auto filterLab = getComponentById<Label>("filter_lib");
  if (filterSubType.length() > 0) {
    filterLab->setString(ScheduleSubTypeData::getScheduleSubTypeDataById(filterSubType)->getName());
  } else {
    filterLab->setString(LocalizationHelper::getLocalization("lab_filter"));
  }
  auto scheduleList = getScheduleDataList(type, filterSubType);
  for (int i = (int)p_selectableComponents.size() - 1; i >= 0; --i) {
    delete p_selectableComponents[i];
  }
  p_selectableComponents.clear();
  p_selectableSpriteComponents.clear();
  int i = 0;
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  
  float height = 61 * scheduleList.size();
  if (height < scrollView->getContentSize().height) {
    height = scrollView->getContentSize().height;
  }
  
  for (auto schedule : scheduleList) {
    CCLOG("selectable: %s", schedule->getName().c_str());
    auto component = generateSelecatableSpriteComponent(schedule);
    p_selectableComponents.push_back(component);
    auto sprite = component->getNode();
    auto listener = BaseSpriteListener::createWithNode(sprite, false);
    listener->setTouchClicked(CC_CALLBACK_2(PracticePanel::selectSchedule, this), nullptr);
    sprite->setPosition(Vec2(0, height - i * 61));
    scrollView->addChild(sprite);
    ++i;
  }
  scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, height));
}

SpriteComponent* PracticePanel::generateSelecatableSpriteComponent(SelectableScheduleData *selectableData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("selectablePracticeSprite"));
  component->setId(selectableData->getId());
  component->addComponentToParent(p_selectableSpriteComponents);
  component->setAssociateData(selectableData);
  auto labelComponent = component->getChildComponentById("selectable_lab");
  labelComponent->setAssociateData(selectableData);
  auto label = dynamic_cast<Label *>(labelComponent->getNode());
  auto text = selectableData->getName() + " ";
  auto proficiencyData = selectableData->getProficiencyData();
  if (proficiencyData != nullptr) {
    text += selectableData->getTypeData()->getProficienceWord() + ": ";
    text += to_string(proficiencyData->getValue()) + "/" + to_string(proficiencyData->getMaxValue());
  }
  label->setString(text);
  return component;
}

void PracticePanel::selectSchedule(Touch* touch, Event* event)
{
  auto sprite = event->getCurrentTarget();
  CCLOG("click : %s", sprite->getName().c_str());
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  if (!BaseSpriteListener::isTouchInsideNode(touch, scrollView)) {
    CCLOG("touch is out side the view, it doesn't count");
    return;
  }
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
    mySchedule->setScheduleId("sleep");
    auto label = getComponentById<Label>("practice_selected_lab_" + mySchedule->getId());
    showMyScheduleOnLabel(mySchedule, label);
  }
}
