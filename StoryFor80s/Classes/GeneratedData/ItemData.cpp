/*
This file (ItemData.cpp) is generated
*/
#include "ItemData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ItemData*>* ItemData::p_sharedDictionary = nullptr;

string ItemData::getId() const
{
	return to_string(p_itemId);
}

string ItemData::getItemId() const
{
	return p_itemId;
}

string ItemData::getName() const
{
	string localId = "item_name_" + to_string(p_itemId);
	return LocalizationHelper::getLocalization(localId);
}

string ItemData::getCondition() const
{
	return p_condition;
}

ItemCategoryData* ItemData::getCategoryData() const
{
	return ItemCategoryData::getItemCategoryDataById(p_categoryId);
}

string ItemData::getCategoryId() const
{
	return p_categoryId;
}

int ItemData::getPrice() const
{
	return p_price;
}

bool ItemData::getHaveIt() const
{
	return p_haveIt;
}

void ItemData::setHaveIt(bool haveIt)
{
	p_haveIt = haveIt;
}

string ItemData::description() const
{
	string desc = "itemData = {\n";
	desc += "\titemId : " + to_string(p_itemId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tcategory : " + to_string(p_categoryId) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\thaveIt : " + to_string(p_haveIt) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ItemData*>* ItemData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ItemData*>();
		static string resPath = "res/base/data/item.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ItemData* itemData = new ItemData();
				itemData->p_itemId = buffer->getString();
				itemData->p_condition = buffer->getString();
				itemData->p_categoryId = buffer->getString();
				itemData->p_price = buffer->getInt();
				itemData->p_haveIt = buffer->getChar();
				p_sharedDictionary->insert(pair<string, ItemData*>(itemData->p_itemId, itemData));
			}
		}
	}
	return p_sharedDictionary;
}

ItemData* ItemData::getItemDataById(const string& itemId)
{
	if (ItemData::getSharedDictionary()->count(itemId)) {
		return ItemData::getSharedDictionary()->at(itemId);
	}
	return nullptr;
}

bool ItemData::saveData(const string & path)
{
	auto filePath = path + "/ItemData.dat";
	auto dict = ItemData::getSharedDictionary();
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

bool ItemData::loadData(const string & path)
{
	auto filePath = path + "/ItemData.dat";
	auto dict = ItemData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			ItemData *data = nullptr;
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

bool ItemData::clearData()
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

void ItemData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "haveIt") {
		this->setHaveIt((atoi(value.c_str()) != 0));
	}
}

string ItemData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "itemId") {
		return to_string(this->getItemId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "category") {
		return to_string(this->getCategoryId());
	} else if (fieldName == "price") {
		return to_string(this->getPrice());
	} else if (fieldName == "haveIt") {
		return to_string(this->getHaveIt());
	}
	CCLOGWARN("Couldn't recognize %s in ItemData", fieldName.c_str());
	return "";
}

BaseData* ItemData::getDataByField(const string & fieldName) const
{
	if (fieldName == "category") {
		return this->getCategoryData();
	}
	CCLOGWARN("Couldn't recognize %s in ItemData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ItemData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ItemData", fieldName.c_str());
	return vector<BaseData *>();
}

