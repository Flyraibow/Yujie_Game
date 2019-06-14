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

class SelectableScheduleData;

namespace game {
  // return how much value is gained.
  int changeProficiency(string proficiencyId, int baseAddValue);
  SelectableScheduleData *getRandomSelectableRelaxSchedule();
}

#endif /* GameLogicFunction_hpp */
