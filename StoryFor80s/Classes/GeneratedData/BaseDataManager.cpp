/*
This file (BaseDataManager.cpp) is generated
*/
#include "BaseDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "HobbyData.hpp"
#include "FatherJobData.hpp"
#include "StoryData.hpp"
#include "SkillsData.hpp"
#include "ItemData.hpp"
#include "FriendData.hpp"
#include "AttributeData.hpp"
#include "WorkData.hpp"
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

HobbyData* BaseDataManager::getHobbyDataById(const string& hobbyId)
{
	if (HobbyData::getSharedDictionary()->count(hobbyId)) {
		return HobbyData::getSharedDictionary()->at(hobbyId);
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

StoryData* BaseDataManager::getStoryDataById(const string& storyId)
{
	if (StoryData::getSharedDictionary()->count(storyId)) {
		return StoryData::getSharedDictionary()->at(storyId);
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

SocialActionData* BaseDataManager::getSocialActionDataById(const string& socialActionId)
{
	if (SocialActionData::getSharedDictionary()->count(socialActionId)) {
		return SocialActionData::getSharedDictionary()->at(socialActionId);
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

WorkData* BaseDataManager::getWorkDataById(const string& actionId)
{
	if (WorkData::getSharedDictionary()->count(actionId)) {
		return WorkData::getSharedDictionary()->at(actionId);
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
	if (!HobbyData::saveData(path)) {
		CCLOG("Failed to save HobbyData, %s", path.c_str());
		return false;
	}
	if (!FatherJobData::saveData(path)) {
		CCLOG("Failed to save FatherJobData, %s", path.c_str());
		return false;
	}
	if (!StoryData::saveData(path)) {
		CCLOG("Failed to save StoryData, %s", path.c_str());
		return false;
	}
	if (!SkillsData::saveData(path)) {
		CCLOG("Failed to save SkillsData, %s", path.c_str());
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
	if (!HobbyData::loadData(path)) {
		CCLOG("Failed to load HobbyData, %s", path.c_str());
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
	if (!SkillsData::loadData(path)) {
		CCLOG("Failed to load SkillsData, %s", path.c_str());
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
	return true;
}

bool BaseDataManager::clearData()
{
	HobbyData::clearData();
	FatherJobData::clearData();
	StoryData::clearData();
	SkillsData::clearData();
	ItemData::clearData();
	FriendData::clearData();
	AttributeData::clearData();
	WorkData::clearData();
	GameData::clearData();
	return true;
}

BaseData * BaseDataManager::getData(const string & dataSet, const string & id)
{
	if (dataSet == "ConditionData") {
		return ConditionData::getConditionDataById(id);
	} else if (dataSet == "ConditionCalculationData") {
		return ConditionCalculationData::getConditionCalculationDataById(id);
	} else if (dataSet == "HobbyData") {
		return HobbyData::getHobbyDataById(id);
	} else if (dataSet == "FatherJobData") {
		return FatherJobData::getFatherJobDataById(id);
	} else if (dataSet == "StoryData") {
		return StoryData::getStoryDataById(id);
	} else if (dataSet == "SkillsData") {
		return SkillsData::getSkillsDataById(id);
	} else if (dataSet == "SocialActionData") {
		return SocialActionData::getSocialActionDataById(id);
	} else if (dataSet == "ItemData") {
		return ItemData::getItemDataById(id);
	} else if (dataSet == "ItemCategoryData") {
		return ItemCategoryData::getItemCategoryDataById(id);
	} else if (dataSet == "FriendData") {
		return FriendData::getFriendDataById(id);
	} else if (dataSet == "ParentChatData") {
		return ParentChatData::getParentChatDataById(id);
	} else if (dataSet == "AttributeData") {
		return AttributeData::getAttributeDataById(id);
	} else if (dataSet == "EventData") {
		return EventData::getEventDataById(id);
	} else if (dataSet == "FunctionCalculationData") {
		return FunctionCalculationData::getFunctionCalculationDataById(id);
	} else if (dataSet == "WorkData") {
		return WorkData::getWorkDataById(id);
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
	if (dataSet == "HobbyData") {
		auto data = HobbyData::getHobbyDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "FatherJobData") {
		auto data = FatherJobData::getFatherJobDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "StoryData") {
		auto data = StoryData::getStoryDataById(id);
		data->setFieldValue(fieldName, value);
	} else if (dataSet == "SkillsData") {
		auto data = SkillsData::getSkillsDataById(id);
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
	}
	CCLOGWARN("Couldn't recognize %s file", dataSet.c_str());
}

