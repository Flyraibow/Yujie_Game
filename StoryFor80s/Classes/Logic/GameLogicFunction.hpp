//
//  GameLogicFunction.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#ifndef GameLogicFunction_hpp
#define GameLogicFunction_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class SchoolStudyData;
class SelectableScheduleData;
class ProficiencyData;
class ProficiencyCategoryData;
class AchievementsData;
class AchievementCategoryData;
class ItemData;

namespace game {
  // return how much value is gained.
  int changeProficiency(const SelectableScheduleData* selectableData);
  int changeProficiency(const SchoolStudyData* schoolData);
  SelectableScheduleData *getRandomSelectableRelaxSchedule();
  vector<AchievementsData *> getMyAchievements(const string &filter = "");
  vector<ProficiencyData *> getMyProficiencies(const string &filter = "");
  vector<ItemData *> getMyItems();
  vector<ProficiencyCategoryData *> getAllProficiencyCategories();
  vector<AchievementCategoryData *> getAllAchievementCategories();
}

#endif /* GameLogicFunction_hpp */
