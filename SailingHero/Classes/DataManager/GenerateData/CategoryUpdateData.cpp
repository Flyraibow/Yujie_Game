/*
This file (CategoryUpdateData.cpp) is generated
*/
#include "CategoryUpdateData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

unordered_map<string, CategoryUpdateData*>* CategoryUpdateData::p_sharedDictionary = nullptr;

string CategoryUpdateData::getCategoryUpdateId() const
{
	return p_categoryUpdateId;
}

string CategoryUpdateData::getCategoryUpdateName() const
{
	string localId = "categoryUpdate_categoryUpdateName_" + p_categoryUpdateId;
	return LocalizationHelper::getLocalization(localId);
}

unordered_set<int> CategoryUpdateData::getUpdateMonth() const
{
	return p_updateMonth;
}

string CategoryUpdateData::description() const
{
	string desc = "categoryUpdateData = {\n";
	desc += "\tcategoryUpdateId : " + to_string(p_categoryUpdateId) + "\n";
	desc += "\tcategoryUpdateName : " + getCategoryUpdateName() + "\n";
	desc += "\tupdateMonth : " + to_string(p_updateMonth) + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, CategoryUpdateData*>* CategoryUpdateData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new unordered_map<string, CategoryUpdateData*>();
		static string resPath = "res/base/data/categoryUpdate.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CategoryUpdateData* categoryUpdateData = new CategoryUpdateData();
				categoryUpdateData->p_categoryUpdateId = buffer->getString();
				auto updateMonthCount = buffer->getLong();
				for (int j = 0; j < updateMonthCount; ++j) {
					categoryUpdateData->p_updateMonth.insert(buffer->getInt());
				}
				p_sharedDictionary->insert(pair<string, CategoryUpdateData*>(categoryUpdateData->p_categoryUpdateId, categoryUpdateData));
			}
		}
	}
	return p_sharedDictionary;
}

CategoryUpdateData* CategoryUpdateData::getCategoryUpdateDataById(const string& categoryUpdateId)
{
	if (CategoryUpdateData::getSharedDictionary()->count(categoryUpdateId)) {
		return CategoryUpdateData::getSharedDictionary()->at(categoryUpdateId);
	}
	CCLOGERROR("invalid categoryUpdateId %s", categoryUpdateId.c_str());
	return nullptr;
}

