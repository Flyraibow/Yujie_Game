//
//  SHGameDataHelper.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SHGameDataHelper.hpp"
#include "LocalizationHelper.hpp"
#include "GameData.hpp"
#include "Calendar.hpp"
#include "Utils.hpp"

using namespace std;

string getHeroFullName(HeroData *heroData)
{
  return heroData->getHeroFirstName() + " · " + heroData->getHeroLastName();
}

string getHeroBirthName(HeroData *heroData)
{
  return format(LocalizationHelper::getLocalization("birth_display").c_str(), heroData->getBirthMonth(), heroData->getBirthDay());
}

string getGameDate()
{
  auto gameData = GameData::getSharedInstance();
  return format(LocalizationHelper::getLocalization("date_display").c_str(), gameData->getMonth(), gameData->getDay());
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
