/*
This file (CategoryUpdateData.cpp) is generated
*/
#include "CategoryUpdateData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace std;

map<int, CategoryUpdateData*>* CategoryUpdateData::p_sharedDictionary = nullptr;

string CategoryUpdateData::getId() const
{
	return to_string(p_categoryUpdateId);
}

int CategoryUpdateData::getCategoryUpdateId() const
{
	return p_categoryUpdateId;
}

string CategoryUpdateData::getCategoryUpdateName() const
{
	string localId = "categoryUpdate_categoryUpdateName_" + to_string(p_categoryUpdateId);
	return LocalizationHelper::getLocalization(localId);
}

set<int> CategoryUpdateData::getUpdateMonth() const
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

map<int, CategoryUpdateData*>* CategoryUpdateData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CategoryUpdateData*>();
		static string resPath = "res/base/data/categoryUpdate.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CategoryUpdateData* categoryUpdateData = new CategoryUpdateData();
				categoryUpdateData->p_categoryUpdateId = buffer->getInt();
				auto updateMonthCount = buffer->getLong();
				for (int j = 0; j < updateMonthCount; ++j) {
					categoryUpdateData->p_updateMonth.insert(buffer->getInt());
				}
				p_sharedDictionary->insert(pair<int, CategoryUpdateData*>(categoryUpdateData->p_categoryUpdateId, categoryUpdateData));
			}
		}
	}
	return p_sharedDictionary;
}

CategoryUpdateData* CategoryUpdateData::getCategoryUpdateDataById(int categoryUpdateId)
{
	if (CategoryUpdateData::getSharedDictionary()->count(categoryUpdateId)) {
		return CategoryUpdateData::getSharedDictionary()->at(categoryUpdateId);
	}
	return nullptr;
}

CategoryUpdateData* CategoryUpdateData::getCategoryUpdateDataById(const string& categoryUpdateId)
{
	if (categoryUpdateId.length() == 0) return nullptr;
	return CategoryUpdateData::getCategoryUpdateDataById(atoi(categoryUpdateId.c_str()));
}

