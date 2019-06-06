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
  // TODO:
  // 1. get all schedule events during this month
  auto schedules = findSchedulesInThisMonth();
  string text = "";
  for (auto schedule : schedules) {
    if (schedule->getTypeId() == "SchoolStudy") {
      auto schoolStudyData = schedule->getSchoolStudyData();
      text += schoolStudyData->getDescription() + " ";
      auto profiencyData = schoolStudyData->getProficiencyData();
      // 技能改变
      if (profiencyData != nullptr) {
        int addValue = game::changeProficiency(schoolStudyData->getProficiencyId(), schoolStudyData->getAddProficiency());
        text += profiencyData->getName() + "+" + to_string(addValue) + " ";
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
        text += attribute->getName() + (addValue > 0 ? "+" : "-") + to_string(addValue) + " ";
      }
      text += "\n";
    }
  }
  // 2. get all other events during this month
  
  auto labDescriptionText = getComponentById<BaseLabel>("lab_text");
  labDescriptionText->setString(text);
}
