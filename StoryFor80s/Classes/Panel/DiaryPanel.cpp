//
//  DiaryPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/2/19.
//

#include "DiaryPanel.hpp"
#include "ScheduleData.hpp"
#include "GameData.hpp"
#include "ConditionManager.hpp"
#include "BaseLabel.hpp"
#include "AttributeData.hpp"
#include "GameLogicFunction.hpp"
#include "MyScheduleData.hpp"
#include "GameData.hpp"
#include "BaseButton.hpp"

struct sort_schedule_by_priority
{
  inline bool operator() (const ScheduleData *s1, const ScheduleData *s2)
  {
    return (s1->getPriority() < s2->getPriority());
  }
};

vector<ScheduleData *> findSchedulesInThisMonth()
{
  auto currentDate = GameData::getSharedInstance()->getGameDateData();
  auto allSchedules = ScheduleData::getSharedDictionary();
  vector<ScheduleData *> results;
  for(auto it = allSchedules->begin(); it != allSchedules->end(); ++it) {
    auto schedule = it->second;
    if (!Manager::checkConditionByString(schedule->getCondition())) {
      continue;
    }
    auto scheduleYear = schedule->getYear();
    if (scheduleYear == 0) {
      results.push_back(schedule);
    } else {
      if (currentDate->getYear() == scheduleYear && currentDate->getMonth() == schedule->getMonth()) {
        results.push_back(schedule);
      }
    }
  }
  sort(results.begin(), results.end(), sort_schedule_by_priority());
  return results;
}

BasePanel* DiaryPanel::createPanel()
{
  return new DiaryPanel();
}

DiaryPanel::DiaryPanel() : BasePanel("diaryPanel")
{
}

void DiaryPanel::initialize()
{
  auto schedules = findSchedulesInThisMonth();
  string text = "";
  for (auto schedule : schedules) {
    if (schedule->getTypeId() == "SchoolStudy" && GameData::getSharedInstance()->getSchoolId() == schedule->getSchoolId()) {
      auto schoolStudyDataList = schedule->getSchoolStudyDataVector();
      for (auto schoolStudyData : schoolStudyDataList) {
        text += schoolStudyData->getDescription() + " ";
        auto profiencyData = schoolStudyData->getProficiencyData();
        // 技能改变
        if (profiencyData != nullptr) {
          auto studyFactor = GameData::getSharedInstance()->getSchoolData()->getStudyFactor();
          int addValue = game::changeProficiency(schoolStudyData) * studyFactor;
          text += schoolStudyData->getTypeData()->getProficienceWord() + "+" + to_string(addValue) + " ";
        }
        // 属性改变
        for (auto attributePair : schoolStudyData->getAttributeChangeMap()) {
          auto attribute = AttributeData::getAttributeDataById(attributePair.first);
          auto addValue = attributePair.second;
          auto finalValue = attribute->getValue() + addValue;
          if (finalValue < 0) {
            finalValue = 0;
          }
          attribute->setValue(finalValue);
          text += attribute->getName() + (addValue > 0 ? "+" : "") + to_string(addValue) + " ";
        }
        text += "\n";
      }
    }
  }
  // 2. get all other events during this month
  auto myScheduleMap = *MyScheduleData::getSharedDictionary();
  for (auto schedulePair : myScheduleMap) {
    // 跳过还没有开放的安排
    if (Manager::checkConditionByString(schedulePair.second->getCondition())) {
      auto pressure = AttributeData::getAttributeDataById("pressure")->getValue();
      auto selfRegulation = AttributeData::getAttributeDataById("selfRegulation")->getValue();
      SelectableScheduleData* scheduleData = nullptr;
      bool relax = false;
      if (pressure > selfRegulation) {
        // 如果当前压力高于自律，那么就会偷懒
        relax = true;
        scheduleData = game::getRandomSelectableRelaxSchedule();
        text += "你感觉太累了。";
      }
      if (scheduleData == nullptr) {
        scheduleData = schedulePair.second->getScheduleData();
      }
      text += scheduleData->getDescription() + " ";
      auto profiencyData = scheduleData->getProficiencyData();
      // 技能改变
      if (profiencyData != nullptr) {
        int addValue = game::changeProficiency(scheduleData);
        if (addValue > 0) {
          text += profiencyData->getName() + scheduleData->getTypeData()->getProficienceWord() + "+" + to_string(addValue) + " ";
        } else {
          text += "无法通过学习继续提升" + scheduleData->getTypeData()->getProficienceWord() + "了。 ";
        }
      }
      // 属性改变
      for (auto attributePair : scheduleData->getAttributeChangeMap()) {
        auto attribute = AttributeData::getAttributeDataById(attributePair.first);
        if (attribute == nullptr) {
          text += "Undefined attribute: " + attributePair.first;
          continue;
        }
        auto addValue = attributePair.second;
        auto finalValue = attribute->getValue() + addValue;
        if (finalValue < 0) {
          finalValue = 0;
        }
        attribute->setValue(finalValue);
        text += attribute->getName() + (addValue > 0 ? "+" : "") + to_string(addValue) + " ";
      }
      text += "\n";
    }
  }
  
  auto labDescriptionText = getComponentById<BaseLabel>("lab_text");
  labDescriptionText->setString(text);
}
