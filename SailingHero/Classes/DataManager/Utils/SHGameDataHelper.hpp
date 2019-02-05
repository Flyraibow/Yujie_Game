//
//  SHGameDataHelper.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#ifndef SHGameDataHelper_hpp
#define SHGameDataHelper_hpp

#include <stdio.h>
#include "HeroData.hpp"

#include "FunctionCalculationData.hpp"

using namespace std;

string getHeroDialogName(HeroData *heroData, bool showFullName);
string getGameDate();

namespace SHFunction {
  BaseData* getDataFromFunctionData(FunctionCalculationData *functionData);
}

#endif /* SHGameDataHelper_hpp */
