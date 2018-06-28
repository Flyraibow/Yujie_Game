/*
This file (ItemData.cpp) is generated at 2018-07-11 01:50:01
*/
#include "ItemData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string ItemData::getItemId() const
{
	return p_itemId;
}

string ItemData::getItemName() const
{
	string localId = "item_itemName_" + p_itemId;
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* ItemData::getIcon() const
{
	static const string s_basePath = "res/base/icon/item/";
	string path = s_basePath + p_iconId;
	return cocos2d::Sprite::create(path);
}

string ItemData::getIconId() const
{
	return p_iconId;
}

ItemCategoryData* ItemData::getItemCategoryData() const
{
	return ItemCategoryData::getItemCategoryDataById(p_itemCategoryId);
}

string ItemData::getItemCategoryId() const
{
	return p_itemCategoryId;
}

int ItemData::getValue() const
{
	return p_value;
}

int ItemData::getJob() const
{
	return p_job;
}

int ItemData::getPrice() const
{
	return p_price;
}

string ItemData::getItemDescription() const
{
	string localId = "item_itemDescription_" + p_itemId;
	return LocalizationHelper::getLocalization(localId);
}

string ItemData::description() const
{
	string desc = "itemData = {\n";
	desc += "\titemId : " + to_string(p_itemId) + "\n";
	desc += "\titemName : " + getItemName() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\titemCategoryId : " + to_string(p_itemCategoryId) + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\tjob : " + to_string(p_job) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\titemDescription : " + getItemDescription() + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, ItemData*>* ItemData::getSharedDictionary()
{
	static unordered_map<string, ItemData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, ItemData*>();
		static string resPath = "res/base/data/item.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemData* itemData = new ItemData();
				itemData->p_itemId = buffer->getString();
				itemData->p_iconId = buffer->getString();
				itemData->p_itemCategoryId = buffer->getString();
				itemData->p_value = buffer->getInt();
				itemData->p_job = buffer->getInt();
				itemData->p_price = buffer->getInt();
				sharedDictionary->insert(pair<string, ItemData*>(itemData->p_itemId, itemData));
			}
		}
	}
	return sharedDictionary;
}

ItemData* ItemData::getItemDataById(const string& itemId)
{
	if (ItemData::getSharedDictionary()->count(itemId)) {
		return ItemData::getSharedDictionary()->at(itemId);
	}
	CCLOGERROR("invalid itemId %s", itemId.c_str());
	return nullptr;
}

