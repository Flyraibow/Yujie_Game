/*
This file (ItemCategoryData.cpp) is generated
*/
#include "ItemCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<string, ItemCategoryData*>* ItemCategoryData::p_sharedDictionary = nullptr;

string ItemCategoryData::getId() const
{
	return to_string(p_itemCategoryId);
}

string ItemCategoryData::getItemCategoryId() const
{
	return p_itemCategoryId;
}

string ItemCategoryData::getName() const
{
	string localId = "itemCategory_name_" + to_string(p_itemCategoryId);
	return LocalizationHelper::getLocalization(localId);
}

string ItemCategoryData::description() const
{
	string desc = "itemCategoryData = {\n";
	desc += "\titemCategoryId : " + to_string(p_itemCategoryId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ItemCategoryData*>* ItemCategoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ItemCategoryData*>();
		static string resPath = "res/base/data/itemCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemCategoryData* itemCategoryData = new ItemCategoryData();
				itemCategoryData->p_itemCategoryId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ItemCategoryData*>(itemCategoryData->p_itemCategoryId, itemCategoryData));
			}
		}
	}
	return p_sharedDictionary;
}

ItemCategoryData* ItemCategoryData::getItemCategoryDataById(const string& itemCategoryId)
{
	if (ItemCategoryData::getSharedDictionary()->count(itemCategoryId)) {
		return ItemCategoryData::getSharedDictionary()->at(itemCategoryId);
	}
	return nullptr;
}

string ItemCategoryData::getFieldValue(const string & fieldName)
{
	if (fieldName == "itemCategoryId") {
		return to_string(this->getItemCategoryId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	}
	CCLOGWARN("Couldn't recognize %s in ItemCategoryData", fieldName.c_str());
	return "";
}

