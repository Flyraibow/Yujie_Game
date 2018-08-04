/*
This file (ItemData.cpp) is generated
*/
#include "ItemData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ItemData*>* ItemData::p_sharedDictionary = nullptr;

string ItemData::getId() const
{
	return to_string(p_itemId);
}

int ItemData::getItemId() const
{
	return p_itemId;
}

string ItemData::getItemName() const
{
	string localId = "item_itemName_" + to_string(p_itemId);
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* ItemData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/item/";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string ItemData::getIconPath()
{
	static const string s_basePath = "res/base/icon/item/";
	return s_basePath + p_iconId;
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
	string localId = "item_itemDescription_" + to_string(p_itemId);
	return LocalizationHelper::getLocalization(localId);
}

string ItemData::description() const
{
	string desc = "itemData = {\n";
	desc += "\titemId : " + to_string(p_itemId) + "\n";
	desc += "\titemName : " + getItemName() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\titemCategory : " + to_string(p_itemCategoryId) + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\tjob : " + to_string(p_job) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\titemDescription : " + getItemDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, ItemData*>* ItemData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ItemData*>();
		static string resPath = "res/base/data/item.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemData* itemData = new ItemData();
				itemData->p_itemId = buffer->getInt();
				itemData->p_iconId = buffer->getString();
				itemData->p_itemCategoryId = buffer->getString();
				itemData->p_value = buffer->getInt();
				itemData->p_job = buffer->getInt();
				itemData->p_price = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ItemData*>(itemData->p_itemId, itemData));
			}
		}
	}
	return p_sharedDictionary;
}

ItemData* ItemData::getItemDataById(int itemId)
{
	if (ItemData::getSharedDictionary()->count(itemId)) {
		return ItemData::getSharedDictionary()->at(itemId);
	}
	return nullptr;
}

ItemData* ItemData::getItemDataById(const string& itemId)
{
	if (itemId.length() == 0) return nullptr;
	return ItemData::getItemDataById(atoi(itemId.c_str()));
}

