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
#include "ZodiacData.hpp"
#include "Utils.hpp"
#include "HeroData.hpp"
#include "DataManager.hpp"

using namespace SHUtil;

string getHeroDialogName(HeroData *heroData, bool showFullName)
{
  if (showFullName) {
    return heroData->getHeroFirstName() + " · " + heroData->getHeroLastName();
  }
  return "<" + heroData->getHeroFirstName() + ">";
}

string getGameDate()
{
  auto gameData = GameData::getSharedInstance();
  return format(LocalizationHelper::getLocalization("date_display").c_str(), to_string(gameData->getMonth()).c_str() , to_string(gameData->getDay()).c_str());
}

ZodiacData* getZodiacFromHero(HeroData *heroData)
{
  if (heroData != nullptr) {
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
  }
  CCLOGERROR("unrecognized hero zodiac");
  return nullptr;
}


BaseData* SHFunction::getDataFromFunctionData(FunctionCalculationData *functionData)
{
  CCASSERT(functionData != nullptr, "Function data is empty");
  auto functionName = functionData->getFunctionName();
  auto parameters = functionData->getParameters();
  if (functionName == "zodiac_from_hero") {
    auto hero = DataManager::getShareInstance()->decipherData<HeroData>(parameters.at(0));
    return getZodiacFromHero(hero);
  } else {
    CCLOGERROR("unrecognized function id: %s", functionData->getId().c_str());
  }
  return nullptr;
}
