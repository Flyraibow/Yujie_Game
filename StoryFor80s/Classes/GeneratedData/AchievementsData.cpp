/*
This file (AchievementsData.cpp) is generated
*/
#include "AchievementsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, AchievementsData*>* AchievementsData::p_sharedDictionary = nullptr;

string AchievementsData::getId() const
{
	return to_string(p_achievementId);
}

string AchievementsData::getAchievementId() const
{
	return p_achievementId;
}

string AchievementsData::getName() const
{
	string localId = "achievements_name_" + to_string(p_achievementId);
	return LocalizationHelper::getLocalization(localId);
}

AchievementCategoryData* AchievementsData::getCategoryData() const
{
	return AchievementCategoryData::getAchievementCategoryDataById(p_categoryId);
}

string AchievementsData::getCategoryId() const
{
	return p_categoryId;
}

int AchievementsData::getValue() const
{
	return p_value;
}

int AchievementsData::getValidUntilYear() const
{
	return p_validUntilYear;
}

int AchievementsData::getValidUntilMonth() const
{
	return p_validUntilMonth;
}

bool AchievementsData::getHaveIt() const
{
	return p_haveIt;
}

void AchievementsData::setHaveIt(bool haveIt)
{
	p_haveIt = haveIt;
}

string AchievementsData::description() const
{
	string desc = "achievementsData = {\n";
	desc += "\tachievementId : " + to_string(p_achievementId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tcategory : " + to_string(p_categoryId) + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\tvalidUntilYear : " + to_string(p_validUntilYear) + "\n";
	desc += "\tvalidUntilMonth : " + to_string(p_validUntilMonth) + "\n";
	desc += "\thaveIt : " + to_string(p_haveIt) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, AchievementsData*>* AchievementsData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, AchievementsData*>();
		static string resPath = "res/base/data/achievements.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				AchievementsData* achievementsData = new AchievementsData();
				achievementsData->p_achievementId = buffer->getString();
				achievementsData->p_categoryId = buffer->getString();
				achievementsData->p_value = buffer->getInt();
				achievementsData->p_validUntilYear = buffer->getInt();
				achievementsData->p_validUntilMonth = buffer->getInt();
				achievementsData->p_haveIt = buffer->getChar();
				p_sharedDictionary->insert(pair<string, AchievementsData*>(achievementsData->p_achievementId, achievementsData));
			}
		}
	}
	return p_sharedDictionary;
}

AchievementsData* AchievementsData::getAchievementsDataById(const string& achievementId)
{
	if (AchievementsData::getSharedDictionary()->count(achievementId)) {
		return AchievementsData::getSharedDictionary()->at(achievementId);
	}
	return nullptr;
}

bool AchievementsData::saveData(const string & path)
{
	auto filePath = path + "/AchievementsData.dat";
	auto dict = AchievementsData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_haveIt");
		buffer->putString(to_string(data->p_haveIt));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool AchievementsData::loadData(const string & path)
{
	auto filePath = path + "/AchievementsData.dat";
	auto dict = AchievementsData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			AchievementsData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_haveIt") {
						data->p_haveIt = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool AchievementsData::clearData()
{
	if (p_sharedDictionary != nullptr) {
		for (auto iter = p_sharedDictionary->begin(); iter != p_sharedDictionary->end(); ++iter) {
			auto data = iter->second;
			delete data;
		}
		delete p_sharedDictionary;
		p_sharedDictionary = nullptr;
	}
	return true;
}

void AchievementsData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "haveIt") {
		this->setHaveIt((atoi(value.c_str()) != 0));
	}
}

string AchievementsData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "achievementId") {
		return to_string(this->getAchievementId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "category") {
		return to_string(this->getCategoryId());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	} else if (fieldName == "validUntilYear") {
		return to_string(this->getValidUntilYear());
	} else if (fieldName == "validUntilMonth") {
		return to_string(this->getValidUntilMonth());
	} else if (fieldName == "haveIt") {
		return to_string(this->getHaveIt());
	}
	CCLOGWARN("Couldn't recognize %s in AchievementsData", fieldName.c_str());
	return "";
}

BaseData* AchievementsData::getDataByField(const string & fieldName) const
{
	if (fieldName == "category") {
		return this->getCategoryData();
	}
	CCLOGWARN("Couldn't recognize %s in AchievementsData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> AchievementsData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in AchievementsData", fieldName.c_str());
	return vector<BaseData *>();
}

