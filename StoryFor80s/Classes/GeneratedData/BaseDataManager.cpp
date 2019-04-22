/*
This file (BaseDataManager.cpp) is generated
*/
#include "BaseDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "FatherJobData.hpp"
#include "StoryData.hpp"
#include "PersonalityData.hpp"
#include "ItemData.hpp"
#include "FriendData.hpp"
#include "AttributeData.hpp"
#include "WorkData.hpp"
#include "GameData.hpp"
#include "ProficiencyData.hpp"




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

FatherJobData* BaseDataManager::getFatherJobDataById(const string& fatherJobId)
{
	if (FatherJobData::getSharedDictionary()->count(fatherJobId)) {
		return FatherJobData::getSharedDictionary()->at(fatherJobId);
	}
	return nullptr;
}

PlayData* BaseDataManager::getPlayDataById(const string& playId)
{
	if (PlayData::getSharedDictionary()->count(playId)) {
		return PlayData::getSharedDictionary()->at(playId);
	}
	return nullptr;
}

StoryData* BaseDataManager::getStoryDataById(const string& storyId)
{
	if (StoryData::getSharedDictionary()->count(storyId)) {
		return StoryData::getSharedDictionary()->at(storyId);
	}
	return nullptr;
}

PersonalityData* BaseDataManager::getPersonalityDataById(const string& attributeId)
{
	if (PersonalityData::getSharedDictionary()->count(attributeId)) {
		return PersonalityData::getSharedDictionary()->at(attributeId);
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

FriendData* BaseDataManager::getFriendDataById(const string& friendId)
{
	if (FriendData::getSharedDictionary()->count(friendId)) {
		return FriendData::getSharedDictionary()->at(friendId);
	}
	return nullptr;
}

ParentChatData* BaseDataManager::getParentChatDataById(const string& chatId)
{
	if (ParentChatData::getSharedDictionary()->count(chatId)) {
		return ParentChatData::getSharedDictionary()->at(chatId);
	}
	return nullptr;
}

SelfStudyData* BaseDataManager::getSelfStudyDataById(const string& selfStudyId)
{
	if (SelfStudyData::getSharedDictionary()->count(selfStudyId)) {
		return SelfStudyData::getSharedDictionary()->at(selfStudyId);
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

FunctionCalculationData* BaseDataManager::getFunctionCalculationDataById(const string& functionCalculatonId)
{
	if (FunctionCalculationData::getSharedDictionary()->count(functionCalculatonId)) {
		return FunctionCalculationData::getSharedDictionary()->at(functionCalculatonId);
	}
	return nullptr;
}

WorkData* BaseDataManager::getWorkDataById(const string& actionId)
{
	if (WorkData::getSharedDictionary()->count(actionId)) {
		return WorkData::getSharedDictionary()->at(actionId);
	}
	return nullptr;
}

SchoolStudyData* BaseDataManager::getSchoolStudyDataById(const string& schoolStudyId)
{
	if (SchoolStudyData::getSharedDictionary()->count(schoolStudyId)) {
		return SchoolStudyData::getSharedDictionary()->at(schoolStudyId);
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

SchoolData* BaseDataManager::getSchoolDataById(const string& schoolId)
{
	if (SchoolData::getSharedDictionary()->count(schoolId)) {
		return SchoolData::getSharedDictionary()->at(schoolId);
	}
	return nullptr;
}

ProficiencyData* BaseDataManager::getProficiencyDataById(const string& proficiencyId)
{
	if (ProficiencyData::getSharedDictionary()->count(proficiencyId)) {
		return ProficiencyData::getSharedDictionary()->at(proficiencyId);
	}
	return nullptr;
}

bool BaseDataManager::saveData(string fileName)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/gameData_" + fileName;
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
	}
	if (!FatherJobData::saveData(path)) {
		CCLOG("Failed to save FatherJobData, %s", path.c_str());
		return false;
	}
	if (!StoryData::saveData(path)) {
		CCLOG("Failed to save StoryData, %s", path.c_str());
		return false;
	}
	if (!PersonalityData::saveData(path)) {
		CCLOG("Failed to save PersonalityData, %s", path.c_str());
		return false;
	}
	if (!ItemData::saveData(path)) {
		CCLOG("Failed to save ItemData, %s", path.c_str());
		return false;
	}
	if (!FriendData::saveData(path)) {
		CCLOG("Failed to save FriendData, %s", path.c_str());
		return false;
	}
	if (!AttributeData::saveData(path)) {
		CCLOG("Failed to save AttributeData, %s", path.c_str());
		return false;
	}
	if (!WorkData::saveData(path)) {
		CCLOG("Failed to save WorkData, %s", path.c_str());
		return false;
	}
	if (!GameData::saveData(path)) {
		CCLOG("Failed to save GameData, %s", path.c_str());
		return false;
	}
	if (!ProficiencyData::saveData(path)) {
		CCLOG("Failed to save ProficiencyData, %s", path.c_str());
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
	if (!FatherJobData::loadData(path)) {
		CCLOG("Failed to load FatherJobData, %s", path.c_str());
		return false;
	}
	if (!StoryData::loadData(path)) {
		CCLOG("Failed to load StoryData, %s", path.c_str());
		return false;
	}
	if (!PersonalityData::loadData(path)) {
		CCLOG("Failed to load PersonalityData, %s", path.c_str());
		return false;
	}
	if (!ItemData::loadData(path)) {
		CCLOG("Failed to load ItemData, %s", path.c_str());
		return false;
	}
	if (!FriendData::loadData(path)) {
		CCLOG("Failed to load FriendData, %s", path.c_str());
		return false;
	}
	if (!AttributeData::loadData(path)) {
		CCLOG("Failed to load AttributeData, %s", path.c_str());
		return false;
	}
	if (!WorkData::loadData(path)) {
		CCLOG("Failed to load WorkData, %s", path.c_str());
		return false;
	}
	if (!GameData::loadData(path)) {
		CCLOG("Failed to load GameData, %s", path.c_str());
		return false;
	}
	if (!ProficiencyData::loadData(path)) {
		CCLOG("Failed to load ProficiencyData, %s", path.c_str());
		return false;
	}
	return true;
}

bool BaseDataManager::clearData()
{
	FatherJobData::clearData();
	StoryData::clearData();
	PersonalityData::clearData();
	ItemData::clearData();
	FriendData::clearData();
	AttributeData::clearData();
	WorkData::clearData();
	GameData::clearData();
	ProficiencyData::clearData();
	return true;
}

BaseData * BaseDataManager::getData(const string & dataSet, const string & id)
{
	if (dataSet == "ConditionData") {
		return ConditionData::getConditionDataById(id);
	} else if (dataSet == "ConditionCalculationData") {
		return ConditionCalculationData::getConditionCalculationDataById(id);
	} else if (dataSet == "FatherJobData") {
		return FatherJobData::getFatherJobDataById(id);
	} else if (dataSet == "PlayData") {
		return PlayData::getPlayDataById(id);
	} else if (dataSet == "StoryData") {
		return StoryData::getStoryDataById(id);
	} else if (dataSet == "PersonalityData") {
		return PersonalityData::getPersonalityDataById(id);
	} else if (dataSet == "ItemData") {
		return ItemData::getItemDataById(id);
	} else if (dataSet == "ItemCategoryData") {
		return ItemCategoryData::getItemCategoryDataById(id);
	} else if (dataSet == "FriendData") {
		return FriendData::getFriendDataById(id);
	} else if (dataSet == "ParentChatData") {
		return ParentChatData::getParentChatDataById(id);
	} else if (dataSet == "SelfStudyData") {
		return SelfStudyData::getSelfStudyDataById(id);
	} else if (dataSet == "AttributeData") {
		return AttributeData::getAttributeDataById(id);
	} else if (dataSet == "FunctionCalculationData") {
		return FunctionCalculationData::getFunctionCalculationDataById(id);
	} else if (dataSet == "WorkData") {
		return WorkData::getWorkDataById(id);
	} else if (dataSet == "SchoolStudyData") {
		return SchoolStudyData::getSchoolStudyDataById(id);
	} else if (dataSet == "ActionData") {
		return ActionData::getActionDataById(id);
	} else if (dataSet == "GameData") {
		return GameData::getSharedInstance();
	} else if (dataSet == "SchoolData") {
		return SchoolData::getSchoolDataById(id);
	} else if (dataSet == "ProficiencyData") {
		return ProficiencyData::getProficiencyDataById(id);
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
	return nullptr;
}

string BaseDataManager::getDataField(const string & dataSet, const string & id, const string & fieldName)
{
	auto data = getData(dataSet, id);
	if (data != nullptr) {
		return data->getFieldValue(fieldName);
	} else if (dataSet == "ClassScheduleData") {
		return ClassScheduleData::getClassSchedule(id, fieldName);
	}
	return "";
}

void BaseDataManager::setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value)
{
	if (dataSet == "FatherJobData") {
		auto data = FatherJobData::getFatherJobDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "StoryData") {
		auto data = StoryData::getStoryDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "PersonalityData") {
		auto data = PersonalityData::getPersonalityDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "ItemData") {
		auto data = ItemData::getItemDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "FriendData") {
		auto data = FriendData::getFriendDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "AttributeData") {
		auto data = AttributeData::getAttributeDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "WorkData") {
		auto data = WorkData::getWorkDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "GameData") {
		auto data = GameData::getSharedInstance();
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "ProficiencyData") {
		auto data = ProficiencyData::getProficiencyDataById(id);
		data->setFieldValue(fieldName, value);
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
}

vector<BaseData *> BaseDataManager::getDataList(const string & dataSet)
{
	vector<BaseData *> result;
	if (dataSet == "ConditionData") {
		auto dataMap = ConditionData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ConditionCalculationData") {
		auto dataMap = ConditionCalculationData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "FatherJobData") {
		auto dataMap = FatherJobData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "PlayData") {
		auto dataMap = PlayData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "StoryData") {
		auto dataMap = StoryData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "PersonalityData") {
		auto dataMap = PersonalityData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ItemData") {
		auto dataMap = ItemData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ItemCategoryData") {
		auto dataMap = ItemCategoryData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "FriendData") {
		auto dataMap = FriendData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ParentChatData") {
		auto dataMap = ParentChatData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "SelfStudyData") {
		auto dataMap = SelfStudyData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "AttributeData") {
		auto dataMap = AttributeData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "FunctionCalculationData") {
		auto dataMap = FunctionCalculationData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "WorkData") {
		auto dataMap = WorkData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "SchoolStudyData") {
		auto dataMap = SchoolStudyData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ActionData") {
		auto dataMap = ActionData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "SchoolData") {
		auto dataMap = SchoolData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else if (dataSet == "ProficiencyData") {
		auto dataMap = ProficiencyData::getSharedDictionary();
		for (auto elem : *dataMap) {
			result.push_back(elem.second);
		}
	} else {
		CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
	}
	return result;
}

