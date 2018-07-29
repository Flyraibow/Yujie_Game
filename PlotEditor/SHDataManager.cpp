#include "SHDataManager.h"

#include "DataManager/GenerateData/GuildData.hpp"
#include "DataManager/GenerateData/CityData.hpp"
#include "DataManager/GenerateData/CityGoodsData.hpp"

namespace SailingHeroAPI {

SHDataManager SHDataManager::instance;

SHDataManager * SHDataManager::getInstance()
{
    return &instance;
}

void SHDataManager::loadData(std::string basePath)
{
    if (!GuildData::loadData(basePath)) {
        CCLOG("Failed to load GuildData, %s", basePath.c_str());
    }
    if (!CityGoodsData::loadData(basePath)) {
        CCLOG("Failed to load CityGoodsData, %s", basePath.c_str());
    }
    if (!CityData::loadData(basePath)) {
        CCLOG("Failed to load CityData, %s", basePath.c_str());
    }
    if (!GameData::loadData(basePath)) {
        CCLOG("Failed to load GameData, %s", basePath.c_str());
    }
    if (!HeroData::loadData(basePath)) {
        CCLOG("Failed to load HeroData, %s", basePath.c_str());
    }
    CCLOG("All data loaded!");
}

GameData * SHDataManager::getGameData()
{
    return GameData::getSharedInstance();
}

DialogData * SHDataManager::getDialogData(std::string dialogId)
{
    return DialogData::getSharedDictionary()->at(dialogId);
}

HeroData * SHDataManager::getHeroData(int heroId)
{
    return HeroData::getSharedDictionary()->at(heroId);
}

}
