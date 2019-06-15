//
//  GameLogicFunction.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#include "GameLogicFunction.hpp"
#include "ProficiencyData.hpp"
#include "SelectableScheduleData.hpp"
#include "ConditionManager.hpp"
#include "SchoolStudyData.hpp"

namespace game {
  int changeProficiency(const string &proficiencyId, int baseAddValue, const map<string, int> &proficiencDependency, int stopGrowAt)
  {
    auto proficiency = ProficiencyData::getProficiencyDataById(proficiencyId);
    if (proficiency != nullptr) {
      // 增加熟练度
      // depend on 的 attribute 和 value
      double ratio = 1.0;
      for (auto attributePair : proficiency->getAttributeDependOnMap()) {
        auto attribute = AttributeData::getAttributeDataById(attributePair.first);
        if (attribute != nullptr) {
          auto myValue = attribute->getValue();
          auto requireValue = attributePair.second;
          if (myValue > requireValue) {
            ratio *= 1 + 1.0 * (myValue - requireValue) / myValue;
          } else {
            ratio *= 1 + 1.0 * (myValue - requireValue) / requireValue;
          }
        } else {
          CCLOGERROR("couldn't find the attribute: %s in proficiency : %s", attributePair.first.c_str(), proficiency->getName().c_str());
        }
      }
      for (auto profiencyPair : proficiencDependency) {
        auto proficiencyData = ProficiencyData::getProficiencyDataById(profiencyPair.first);
        if (proficiencyData != nullptr) {
          auto myValue = proficiencyData->getValue();
          auto requireValue = profiencyPair.second;
          if (myValue > requireValue) {
            ratio *= 1 + 1.0 * (myValue - requireValue) / myValue;
          } else {
            ratio *= 1 + 1.0 * (myValue - requireValue) / requireValue;
          }
        } else {
          CCLOGERROR("couldn't find the depend profiency: %s in proficiency : %s", profiencyPair.first.c_str(), proficiency->getName().c_str());
        }
      }
      int addValue = int (baseAddValue * ratio + 0.5);
      CCLOG("base profienciency : %d, ratio : %f, result : %d", baseAddValue, ratio, addValue);
      int finalValue = addValue + proficiency->getValue();
      if (finalValue > proficiency->getMaxValue()) {
        finalValue = proficiency->getMaxValue();
      }
      if (stopGrowAt > 0 && finalValue > stopGrowAt) {
        finalValue = stopGrowAt;
      }
      auto realAddValue = finalValue - proficiency->getValue();
      proficiency->setValue(finalValue);
      return realAddValue;
    } else {
      
      CCLOGERROR("unrecoginized proficiency : %s", proficiencyId.c_str());
    }
    
    return 0;
  }
}

int game::changeProficiency(const SelectableScheduleData* selectableData)
{
  return changeProficiency(
                           selectableData->getProficiencyId(),
                           selectableData->getAddProficiency(),
                           selectableData->getProficiencyDependOnMap(),
                           selectableData->getStopGrowAt());
}

int game::changeProficiency(const SchoolStudyData* schoolData)
{
  return changeProficiency(
                           schoolData->getProficiencyId(),
                           schoolData->getAddProficiency(),
                           schoolData->getProficiencyDependOnMap(),
                           schoolData->getStopGrowAt());
}

SelectableScheduleData* game::getRandomSelectableRelaxSchedule()
{
  int totalAddiction = 0;
  vector<pair<SelectableScheduleData *, int>> list;
  auto selectableDataMap = *SelectableScheduleData::getSharedDictionary();
  for (auto selectableDataPair : selectableDataMap) {
    auto selecableData = selectableDataPair.second;
    if (!Manager::checkConditionByString(selecableData->getCondition())) {
      continue;
    }
    if (selecableData->getAddictions()) {
      totalAddiction += selecableData->getAddictions();
      list.push_back(make_pair(selecableData, totalAddiction));
    }
  }
  auto randomAddiction = arc4random() % totalAddiction;
  for (auto selectablePair : list) {
    if (randomAddiction < selectablePair.second) {
      return selectablePair.first;
    }
  }
  CCLOGERROR("Couldn't get random addiction relax schedule");
  return nullptr;
}
