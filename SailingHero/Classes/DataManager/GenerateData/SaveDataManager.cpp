/*
This file (SaveDataManager.cpp) is generated at 2018-07-11 01:50:01
*/
#include "SaveDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "HeroData.hpp"

using namespace std;
bool SaveDataManager::saveData(int index)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + to_string(index);
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
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
	}
	if (!HeroData::loadData(path)) {
		CCLOG("Failed to load HeroData, %s", path.c_str());
		return false;
	}
	return true;
}

