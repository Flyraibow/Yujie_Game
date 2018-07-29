/*
This file (ItemCategoryData.cpp) is generated
*/
#include "ItemCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ItemCategoryData*>* ItemCategoryData::p_sharedDictionary = nullptr;

string ItemCategoryData::getId() const
{
	return to_string(p_itemCategoryId);
}

int ItemCategoryData::getItemCategoryId() const
{
	return p_itemCategoryId;
}

string ItemCategoryData::getItemCategoryName() const
{
	string localId = "itemCategory_itemCategoryName_" + to_string(p_itemCategoryId);
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

map<int, ItemCategoryData*>* ItemCategoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ItemCategoryData*>();
		static string resPath = "res/base/data/itemCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemCategoryData* itemCategoryData = new ItemCategoryData();
				itemCategoryData->p_itemCategoryId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ItemCategoryData*>(itemCategoryData->p_itemCategoryId, itemCategoryData));
			}
		}
	}
	return p_sharedDictionary;
}

ItemCategoryData* ItemCategoryData::getItemCategoryDataById(int itemCategoryId)
{
	if (ItemCategoryData::getSharedDictionary()->count(itemCategoryId)) {
		return ItemCategoryData::getSharedDictionary()->at(itemCategoryId);
	}
	return nullptr;
}

ItemCategoryData* ItemCategoryData::getItemCategoryDataById(const string& itemCategoryId)
{
	if (itemCategoryId.length() == 0) return nullptr;
	return ItemCategoryData::getItemCategoryDataById(atoi(itemCategoryId.c_str()));
}

