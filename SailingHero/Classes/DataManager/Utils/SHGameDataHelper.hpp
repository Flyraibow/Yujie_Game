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
#include "ZodiacData.hpp"

using namespace std;

string getHeroFullName(HeroData *heroData);
string getHeroBirthName(HeroData *heroData);
ZodiacData* getZodiacFromHero(HeroData *heroData);
bool isBirthValid(int month, int day);

#endif /* SHGameDataHelper_hpp */
