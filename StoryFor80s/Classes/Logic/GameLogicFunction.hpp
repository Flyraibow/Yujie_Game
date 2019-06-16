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
class AchievementsData;
class ItemData;

namespace game {
  // return how much value is gained.
  int changeProficiency(const SelectableScheduleData* selectableData);
  int changeProficiency(const SchoolStudyData* schoolData);
  SelectableScheduleData *getRandomSelectableRelaxSchedule();
  vector<AchievementsData *> getMyAchievements();
  vector<ProficiencyData *> getMyProficiencies();
  vector<ItemData *> getMyItems();
}

#endif /* GameLogicFunction_hpp */
