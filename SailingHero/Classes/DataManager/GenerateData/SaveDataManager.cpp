/*
This file (SaveDataManager.cpp) is generated
*/
#include "SaveDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "GuildData.hpp"
#include "ShipTeamData.hpp"
#include "CityGoodsData.hpp"
#include "CityData.hpp"
#include "GameData.hpp"
#include "HeroData.hpp"




bool SaveDataManager::saveData(int index)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + to_string(index);
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
	}
	if (!GuildData::saveData(path)) {
		CCLOG("Failed to save GuildData, %s", path.c_str());
		return false;
	}
	if (!ShipTeamData::saveData(path)) {
		CCLOG("Failed to save ShipTeamData, %s", path.c_str());
		return false;
	}
	if (!CityGoodsData::saveData(path)) {
		CCLOG("Failed to save CityGoodsData, %s", path.c_str());
		return false;
	}
	if (!CityData::saveData(path)) {
		CCLOG("Failed to save CityData, %s", path.c_str());
		return false;
	}
	if (!GameData::saveData(path)) {
		CCLOG("Failed to save GameData, %s", path.c_str());
		return false;
	}
	if (!HeroData::saveData(path)) {
		CCLOG("Failed to save HeroData, %s", path.c_str());
		return false;
	}
	return true;
}

bool SaveDataManager::loadData(int index)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + to_string(index);
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		CCLOG("Failed to load data, there is no folder %s", path.c_str());
		return false;
	}
	if (!GuildData::loadData(path)) {
		CCLOG("Failed to load GuildData, %s", path.c_str());
		return false;
	}
	if (!ShipTeamData::loadData(path)) {
		CCLOG("Failed to load ShipTeamData, %s", path.c_str());
		return false;
	}
	if (!CityGoodsData::loadData(path)) {
		CCLOG("Failed to load CityGoodsData, %s", path.c_str());
		return false;
	}
	if (!CityData::loadData(path)) {
		CCLOG("Failed to load CityData, %s", path.c_str());
		return false;
	}
	if (!GameData::loadData(path)) {
		CCLOG("Failed to load GameData, %s", path.c_str());
		return false;
	}
	if (!HeroData::loadData(path)) {
		CCLOG("Failed to load HeroData, %s", path.c_str());
		return false;
	}
	return true;
}

bool SaveDataManager::clearData()
{
	GuildData::clearData();
	ShipTeamData::clearData();
	CityGoodsData::clearData();
	CityData::clearData();
	GameData::clearData();
	HeroData::clearData();
	return true;
}

