/*
This file (BaseDataManager.cpp) is generated
*/
#include "BaseDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "SkillsData.hpp"
#include "ItemData.hpp"
#include "AttributeData.hpp"
#include "GameData.hpp"




ConditionData* BaseDataManager::getConditionDataById(const string& conditionId)
{
	if (ConditionData::getSharedDictionary()->count(conditionId)) {
		return ConditionData::getSharedDictionary()->at(conditionId);
	}
	return nullptr;
}

ConditionCalculationData* BaseDataManager::getConditionCalculationDataById(const string& conditionCalculationId)
{
	if (ConditionCalculationData::getSharedDictionary()->count(conditionCalculationId)) {
		return ConditionCalculationData::getSharedDictionary()->at(conditionCalculationId);
	}
	return nullptr;
}

SkillsData* BaseDataManager::getSkillsDataById(const string& skillId)
{
	if (SkillsData::getSharedDictionary()->count(skillId)) {
		return SkillsData::getSharedDictionary()->at(skillId);
	}
	return nullptr;
}

ItemData* BaseDataManager::getItemDataById(const string& itemId)
{
	if (ItemData::getSharedDictionary()->count(itemId)) {
		return ItemData::getSharedDictionary()->at(itemId);
	}
	return nullptr;
}

ItemCategoryData* BaseDataManager::getItemCategoryDataById(const string& itemCategoryId)
{
	if (ItemCategoryData::getSharedDictionary()->count(itemCategoryId)) {
		return ItemCategoryData::getSharedDictionary()->at(itemCategoryId);
	}
	return nullptr;
}

AttributeData* BaseDataManager::getAttributeDataById(const string& attributeId)
{
	if (AttributeData::getSharedDictionary()->count(attributeId)) {
		return AttributeData::getSharedDictionary()->at(attributeId);
	}
	return nullptr;
}

EventData* BaseDataManager::getEventDataById(const string& eventId)
{
	if (EventData::getSharedDictionary()->count(eventId)) {
		return EventData::getSharedDictionary()->at(eventId);
	}
	return nullptr;
}

FunctionCalculationData* BaseDataManager::getFunctionCalculationDataById(const string& functionCalculatonId)
{
	if (FunctionCalculationData::getSharedDictionary()->count(functionCalculatonId)) {
		return FunctionCalculationData::getSharedDictionary()->at(functionCalculatonId);
	}
	return nullptr;
}

ActionData* BaseDataManager::getActionDataById(const string& actionId)
{
	if (ActionData::getSharedDictionary()->count(actionId)) {
		return ActionData::getSharedDictionary()->at(actionId);
	}
	return nullptr;
}

GameData* BaseDataManager::getGameData()
{
	return GameData::getSharedInstance();
}

bool BaseDataManager::saveData(string fileName)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/gameData_" + fileName;
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
	}
	if (!SkillsData::saveData(path)) {
		CCLOG("Failed to save SkillsData, %s", path.c_str());
		return false;
	}
	if (!ItemData::saveData(path)) {
		CCLOG("Failed to save ItemData, %s", path.c_str());
		return false;
	}
	if (!AttributeData::saveData(path)) {
		CCLOG("Failed to save AttributeData, %s", path.c_str());
		return false;
	}
	if (!GameData::saveData(path)) {
		CCLOG("Failed to save GameData, %s", path.c_str());
		return false;
	}
	return true;
}

bool BaseDataManager::loadData(string fileName)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/gameData_" + fileName;
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		CCLOG("Failed to load data, there is no folder %s", path.c_str());
		return false;
	}
	if (!SkillsData::loadData(path)) {
		CCLOG("Failed to load SkillsData, %s", path.c_str());
		return false;
	}
	if (!ItemData::loadData(path)) {
		CCLOG("Failed to load ItemData, %s", path.c_str());
		return false;
	}
	if (!AttributeData::loadData(path)) {
		CCLOG("Failed to load AttributeData, %s", path.c_str());
		return false;
	}
	if (!GameData::loadData(path)) {
		CCLOG("Failed to load GameData, %s", path.c_str());
		return false;
	}
	return true;
}

bool BaseDataManager::clearData()
{
	SkillsData::clearData();
	ItemData::clearData();
	AttributeData::clearData();
	GameData::clearData();
	return true;
}

BaseData * BaseDataManager::getData(const string & dataSet, const string & id)
{
	if (dataSet == "ConditionData") {
		return ConditionData::getConditionDataById(id);
	} else if (dataSet == "ConditionCalculationData") {
		return ConditionCalculationData::getConditionCalculationDataById(id);
	} else if (dataSet == "SkillsData") {
		return SkillsData::getSkillsDataById(id);
	} else if (dataSet == "ItemData") {
		return ItemData::getItemDataById(id);
	} else if (dataSet == "ItemCategoryData") {
		return ItemCategoryData::getItemCategoryDataById(id);
	} else if (dataSet == "AttributeData") {
		return AttributeData::getAttributeDataById(id);
	} else if (dataSet == "EventData") {
		return EventData::getEventDataById(id);
	} else if (dataSet == "FunctionCalculationData") {
		return FunctionCalculationData::getFunctionCalculationDataById(id);
	} else if (dataSet == "ActionData") {
		return ActionData::getActionDataById(id);
	} else if (dataSet == "GameData") {
		return GameData::getSharedInstance();
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
	return nullptr;
}

string BaseDataManager::getDataField(const string & dataSet, const string & id, const string & fieldName)
{
	auto data = getData(dataSet, id);
	if (data != nullptr) {
		return data->getFieldValue(fieldName);
	}
	return "";
}

void BaseDataManager::setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value)
{
	if (dataSet == "SkillsData") {
		auto data = SkillsData::getSkillsDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "ItemData") {
		auto data = ItemData::getItemDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "AttributeData") {
		auto data = AttributeData::getAttributeDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "GameData") {
		auto data = GameData::getSharedInstance();
		data->setFieldValue(fieldName, value);
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
}

