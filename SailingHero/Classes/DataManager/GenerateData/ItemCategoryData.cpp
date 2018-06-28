/*
This file (ItemCategoryData.cpp) is generated at 2018-07-11 01:50:01
*/
#include "ItemCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string ItemCategoryData::getItemCategoryId() const
{
	return p_itemCategoryId;
}

string ItemCategoryData::getItemCategoryName() const
{
	string localId = "itemCategory_itemCategoryName_" + p_itemCategoryId;
	return LocalizationHelper::getLocalization(localId);
}

string ItemCategoryData::description() const
{
	string desc = "itemCategoryData = {\n";
	desc += "\titemCategoryId : " + to_string(p_itemCategoryId) + "\n";
	desc += "\titemCategoryName : " + getItemCategoryName() + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, ItemCategoryData*>* ItemCategoryData::getSharedDictionary()
{
	static unordered_map<string, ItemCategoryData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, ItemCategoryData*>();
		static string resPath = "res/base/data/itemCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemCategoryData* itemCategoryData = new ItemCategoryData();
				itemCategoryData->p_itemCategoryId = buffer->getString();
				sharedDictionary->insert(pair<string, ItemCategoryData*>(itemCategoryData->p_itemCategoryId, itemCategoryData));
			}
		}
	}
	return sharedDictionary;
}

ItemCategoryData* ItemCategoryData::getItemCategoryDataById(const string& itemCategoryId)
{
	if (ItemCategoryData::getSharedDictionary()->count(itemCategoryId)) {
		return ItemCategoryData::getSharedDictionary()->at(itemCategoryId);
	}
	CCLOGERROR("invalid itemCategoryId %s", itemCategoryId.c_str());
	return nullptr;
}

