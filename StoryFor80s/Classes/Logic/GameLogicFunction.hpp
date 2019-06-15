//
//  GameLogicFunction.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#ifndef GameLogicFunction_hpp
#define GameLogicFunction_hpp

#include <stdio.h>

using namespace std;

class SchoolStudyData;
class SelectableScheduleData;
class ProficiencyData;


namespace game {
  // return how much value is gained.
  int changeProficiency(const SelectableScheduleData* selectableData);
  int changeProficiency(const SchoolStudyData* schoolData);
  SelectableScheduleData *getRandomSelectableRelaxSchedule();
}

#endif /* GameLogicFunction_hpp */
