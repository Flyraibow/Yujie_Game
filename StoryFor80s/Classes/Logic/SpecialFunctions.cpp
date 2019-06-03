//
//  SpecialFunctions.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/17/19.
//

#include "SpecialFunctions.hpp"
#include "GameData.hpp"
#include "BaseDataManager.hpp"
#include "SceneManager.hpp"
#include "GameSavingData.hpp"
#include "DataManager.hpp"
#include "BaseGlobalDataManager.hpp"
#include "FunctionManager.hpp"

void story::passDay(const nlohmann::json &jsonContent)
{
  auto gameDate = GameData::getSharedInstance()->getGameDateData();
  auto day = gameDate->getDay();
  auto month = gameDate->getMonth();
  auto year = gameDate->getYear();
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
  gameDate->setDay(day);
  gameDate->setMonth(month);
  gameDate->setYear(year);
}


void game::homePage(const nlohmann::json &jsonContent)
{
  BaseDataManager::clearData();
  SceneManager::getShareInstance()->setScene("menu");
}

void game::save(const nlohmann::json &jsonContent)
{
  auto index = DataManager::getShareInstance()->getTempString("index");
  auto gameSaving = GameSavingData::getGameSavingDataById(index);
  BaseDataManager::saveData(index);
  gameSaving->setSaveDescription(DataManager::getShareInstance()->getTempString("saveDescription"));
  gameSaving->setSaved(true);
  BaseGlobalDataManager::saveData("global");
}

void game::load(const nlohmann::json &jsonContent)
{
  auto index = DataManager::getShareInstance()->getTempString("index");
  BaseDataManager::loadData(index);
}
