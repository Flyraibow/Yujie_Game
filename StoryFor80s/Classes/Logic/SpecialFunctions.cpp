//
//  SpecialFunctions.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/17/19.
//

#include "SpecialFunctions.hpp"
#include "GameData.hpp"

void story::passDay(const nlohmann::json &jsonContent)
{
  auto day = GameData::getSharedInstance()->getDay();
  auto month = GameData::getSharedInstance()->getMonth();
  auto year = GameData::getSharedInstance()->getYear();
  day++;
  if ((day == 29 && month == 2 && year % 4 != 0) ||
      (day == 30 && month == 2) || day == 32 ||
      (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))) {
    month++;
    day = 1;
  }
  if (month == 13) {
    year++;
    month = 1;
  }
  GameData::getSharedInstance()->setDay(day);
  GameData::getSharedInstance()->setMonth(month);
  GameData::getSharedInstance()->setYear(year);
}
