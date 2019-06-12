/*
This file (AchievementCategoryData.cpp) is generated
*/
#include "AchievementCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, AchievementCategoryData*>* AchievementCategoryData::p_sharedDictionary = nullptr;

string AchievementCategoryData::getId() const
{
	return to_string(p_categoryId);
}

string AchievementCategoryData::getCategoryId() const
{
	return p_categoryId;
}

string AchievementCategoryData::getName() const
{
	string localId = "achievementCategory_name_" + to_string(p_categoryId);
	return LocalizationHelper::getLocalization(localId);
}

vector<AchievementCategoryData*> AchievementCategoryData::getSubCategoryDataVector() const
{
	vector<AchievementCategoryData*> resultVector;
	for (auto objId : p_subCategoryIdVector) {
		resultVector.push_back(AchievementCategoryData::getAchievementCategoryDataById(objId));
	}
	return resultVector;
}

vector<string> AchievementCategoryData::getSubCategoryIdVector() const
{
	return p_subCategoryIdVector;
}

string AchievementCategoryData::description() const
{
	string desc = "achievementCategoryData = {\n";
	desc += "\tcategoryId : " + to_string(p_categoryId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tsubCategory : " + to_string(p_subCategoryIdVector) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, AchievementCategoryData*>* AchievementCategoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, AchievementCategoryData*>();
		static string resPath = "res/base/data/achievementCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				AchievementCategoryData* achievementCategoryData = new AchievementCategoryData();
				achievementCategoryData->p_categoryId = buffer->getString();
				auto subCategoryCount = buffer->getLong();
				for (int j = 0; j < subCategoryCount; ++j) {
					achievementCategoryData->p_subCategoryIdVector.push_back(buffer->getString());
				}
				p_sharedDictionary->insert(pair<string, AchievementCategoryData*>(achievementCategoryData->p_categoryId, achievementCategoryData));
			}
		}
	}
	return p_sharedDictionary;
}

AchievementCategoryData* AchievementCategoryData::getAchievementCategoryDataById(const string& categoryId)
{
	if (AchievementCategoryData::getSharedDictionary()->count(categoryId)) {
		return AchievementCategoryData::getSharedDictionary()->at(categoryId);
	}
	return nullptr;
}

string AchievementCategoryData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "categoryId") {
		return to_string(this->getCategoryId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "subCategory") {
		return to_string(this->getSubCategoryIdVector());
	}
	CCLOGWARN("Couldn't recognize %s in AchievementCategoryData", fieldName.c_str());
	return "";
}

BaseData* AchievementCategoryData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in AchievementCategoryData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> AchievementCategoryData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in AchievementCategoryData", fieldName.c_str());
	return vector<BaseData *>();
}

