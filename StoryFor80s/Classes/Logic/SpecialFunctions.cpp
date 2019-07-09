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
#include "TaskLogicFunction.hpp"
#include "JsonUtil.hpp"
#include "TaskData.hpp"
#include "TaskLogicFunction.hpp"


namespace game {
  void saveGlobal()
  {
    BaseGlobalDataManager::saveData("global");
  }
}

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


void story::passMonth(const nlohmann::json &jsonContent)
{
  auto gameDate = GameData::getSharedInstance()->getGameDateData();
  auto month = gameDate->getMonth();
  auto year = gameDate->getYear();
  month++;
  if (month == 13) {
    year++;
    month = 1;
  }
  gameDate->setMonth(month);
  gameDate->setYear(year);
  GameData::getSharedInstance()->setHasTalkedToParent(false);
  // Update all task Information
  game::updateAllTasks();
}

void story::getTask(const nlohmann::json &jsonContent)
{
  auto taskName = Utils::getStringFromJson(jsonContent, "name");
  if (taskName.length() > 0) {
    auto task = TaskData::getTaskDataById(taskName);
    if (task != nullptr) {
      game::startTask(task);
      return;
    }
  }
  CCLOGERROR("un-recognize task %s", jsonContent.dump().c_str());
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
  saveGlobal();
}

void game::load(const nlohmann::json &jsonContent)
{
  auto index = DataManager::getShareInstance()->getTempString("index");
  BaseDataManager::clearData();
  BaseDataManager::loadData(index);
}

void game::saveGlobal(const nlohmann::json &jsonContent)
{
  saveGlobal();
}

#include "audio/include/SimpleAudioEngine.h"

void game::updateSoundVolume(const nlohmann::json &jsonContent)
{
  // initial Music/Effect volume
  auto gameSetting = GameSettingData::getSharedInstance();
  CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(gameSetting->getSoundVolume() / 100.0);
  CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(gameSetting->getEffectVolume() / 100.0);
  saveGlobal();
}
