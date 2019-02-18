/*
This file (BaseGlobalDataManager.cpp) is generated
*/
#include "BaseGlobalDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "GameSavingData.hpp"




GameSavingData* BaseGlobalDataManager::getGameSavingDataById(int savingId)
{
	if (GameSavingData::getSharedDictionary()->count(savingId)) {
		return GameSavingData::getSharedDictionary()->at(savingId);
	}
	return nullptr;
}

GameSavingData* BaseGlobalDataManager::getGameSavingDataById(const string& savingId)
{
	if (savingId.length() == 0) return nullptr;
	return GameSavingData::getGameSavingDataById(atoi(savingId.c_str()));
}

bool BaseGlobalDataManager::saveData(string fileName)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/globalData" + fileName;
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
	}
	if (!GameSavingData::saveData(path)) {
		CCLOG("Failed to save GameSavingData, %s", path.c_str());
		return false;
	}
	return true;
}

bool BaseGlobalDataManager::loadData(string fileName)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/globalData" + fileName;
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		CCLOG("Failed to load data, there is no folder %s", path.c_str());
		return false;
	}
	if (!GameSavingData::loadData(path)) {
		CCLOG("Failed to load GameSavingData, %s", path.c_str());
		return false;
	}
	return true;
}

bool BaseGlobalDataManager::clearData()
{
	GameSavingData::clearData();
	return true;
}

BaseData * BaseGlobalDataManager::getData(const string & dataSet, const string & id)
{
	if (dataSet == "GameSavingData") {
		return GameSavingData::getGameSavingDataById(id);
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
	return nullptr;
}

string BaseGlobalDataManager::getDataField(const string & dataSet, const string & id, const string & fieldName)
{
	auto data = getData(dataSet, id);
	if (data != nullptr) {
		return data->getFieldValue(fieldName);
	}
	return "";
}

void BaseGlobalDataManager::setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value)
{
	if (dataSet == "GameSavingData") {
		auto data = GameSavingData::getGameSavingDataById(id);
		data->setFieldValue(fieldName, value);
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
}

