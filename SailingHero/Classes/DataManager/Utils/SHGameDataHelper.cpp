//
//  SHGameDataHelper.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SHGameDataHelper.hpp"
#include "LocalizationHelper.hpp"
#include "Utils.hpp"

using namespace std;

string getHeroFullName(HeroData *heroData)
{
  return heroData->getHeroFirstName() + " · " + heroData->getHeroLastName();
}

string getHeroBirthName(HeroData *heroData)
{
  return format(LocalizationHelper::getLocalization("birth_dsiplay").c_str(), heroData->getBirthMonth(), heroData->getBirthDay());
}

ZodiacData* getZodiacFromHero(HeroData *heroData)
{
  auto zodiacDic = ZodiacData::getSharedDictionary();
  for (auto iter = zodiacDic->begin(); iter != zodiacDic->end(); ++iter) {
    auto zodiacData = iter->second;
    auto startDate = zodiacData->getStartMonth() * 100 + zodiacData->getStartDate();
    auto endDate = zodiacData->getEndMonth() * 100 + zodiacData->getEndDate();
    auto birthDate = heroData->getBirthMonth() * 100 + heroData->getBirthDay();
    if (endDate < startDate) {
      endDate += 1200;
    }
    if ( startDate <= birthDate && endDate >= birthDate) {
      return zodiacData;
    }
  }
  return nullptr;
}


bool isBirthValid(int month, int day) {
  if (month < 1 || month > 12 || day < 1) {
    return false;
  }
  switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return day <= 31;
    case 2:
      return day <= 28;
    default:
      return day <= 30;
  }
}
