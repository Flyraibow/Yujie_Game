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

using namespace SHUtil;

string getHeroFullName(HeroData *heroData)
{
  return heroData->getHeroFirstName() + " · " + heroData->getHeroLastName();
}

string getHeroDialogName(HeroData *heroData, bool showFullName)
{
  if (showFullName) {
    return getHeroFullName(heroData);
  }
  return "<" + heroData->getHeroFirstName() + ">";
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
  auto birthDate = heroData->getBirthMonth() * 100 + heroData->getBirthDay();
  for (auto iter = zodiacDic->begin(); iter != zodiacDic->end(); ++iter) {
    auto zodiacData = iter->second;
    auto startDate = zodiacData->getStartMonth() * 100 + zodiacData->getStartDate();
    auto endDate = zodiacData->getEndMonth() * 100 + zodiacData->getEndDate();
    if (endDate > startDate) {
      if (startDate <= birthDate && endDate >= birthDate) {
        return zodiacData;
      }
    } else if (startDate <= birthDate || endDate >= birthDate) {
      return zodiacData;
    }
  }
  return nullptr;
}
