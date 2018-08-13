/*
This file (GoodsPricePercentData.cpp) is generated
*/
#include "GoodsPricePercentData.hpp"
#include "ByteBuffer.hpp"



map<int, map<int,int>>* GoodsPricePercentData::p_sharedDictionary = nullptr;

const map<int, map<int,int>>* GoodsPricePercentData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, map<int,int>>();
		static string resPath = "res/base/data/goodsPricePercent.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			vector<int> rowValues;
			auto rowCount = buffer->getLong();
			for (int i = 0; i < rowCount; ++i) {
				rowValues.push_back(buffer->getInt());
			}
			vector<int> colValues;
			auto colCount = buffer->getLong();
			for (int i = 0; i < colCount; ++i) {
				colValues.push_back(buffer->getInt());
			}
			for (int i = 0; i < rowCount; ++i) {
				map<int, int> rowMap;
				for (int j = 0; j < colCount; ++j) {
					int value = buffer->getInt();
					rowMap.insert(make_pair(colValues[j], value));
				}
				p_sharedDictionary->insert(make_pair(rowValues[i], rowMap));
			}
		}
	}
	return p_sharedDictionary;
}

int GoodsPricePercentData::getGoodsPricePercent(int cityId, int goodsCategoryId)
{
	auto dict = getSharedDictionary();
	if (dict->count(cityId)) {
		if (dict->at(cityId).count(goodsCategoryId)) {
			return dict->at(cityId).at(goodsCategoryId);
		} else {
			CCLOGWARN("Couldn't find goodsCategoryId: %s in GoodsPricePercent", to_string(goodsCategoryId).c_str());
		}
	} else {
		CCLOGWARN("Couldn't find cityId: %s in GoodsPricePercent", to_string(cityId).c_str());
	}
	return 0;
}

void GoodsPricePercentData::setGoodsPricePercent(int cityId, int goodsCategoryId, int value)
{
	auto dict = getSharedDictionary();
	if (dict->count(cityId)) {
		if (dict->at(cityId).count(goodsCategoryId)) {
			p_sharedDictionary->at(cityId)[goodsCategoryId] = value;
		} else {
			CCLOGWARN("Couldn't find goodsCategoryId: %s in GoodsPricePercent", to_string(goodsCategoryId).c_str());
		}
	} else {
		CCLOGWARN("Couldn't find cityId: %s in GoodsPricePercent", to_string(cityId).c_str());
	}
}

bool GoodsPricePercentData::saveData(const string & path)
{
	auto filePath = path + "/GoodsPricePercentData.dat";
	auto dict = GoodsPricePercentData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	for (auto iter = dict->begin(); iter != dict->end(); ++iter) {
		buffer->putInt(iter->first);
		auto mapList = iter->second;
		buffer->putLong(mapList.size());
		for (auto it = mapList.begin(); it != mapList.end(); ++it) {
			buffer->putInt(it->first);
			buffer->putString(to_string(it->second));
		}
	}
	buffer->writeToFile(filePath);
	return true;
}

bool GoodsPricePercentData::loadData(const string & path)
{
	auto filePath = path + "/GoodsPricePercentData.dat";
	clearData();
	p_sharedDictionary = new map<int, map<int,int>>();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto rowCount = buffer->getLong();
		for (int i = 0; i < rowCount; ++i) {
			auto rowKey = buffer->getInt();
			auto colCount = buffer->getLong();
			map<int, int> rowMap;
			for (int j = 0; j < colCount; ++j) {
				auto colKey = buffer->getInt();
				auto value = atoi(buffer->getString().c_str());
				rowMap.insert(make_pair(colKey, value));
			}
			p_sharedDictionary->insert(make_pair(rowKey, rowMap));
		}
	}
	return true;
}

bool GoodsPricePercentData::clearData()
{
	if (p_sharedDictionary != nullptr) {
		delete p_sharedDictionary;
		p_sharedDictionary = nullptr;
	}
	return true;
}

void GoodsPricePercentData::setFieldValue(const string & fieldName, const string & value)
{
}

string GoodsPricePercentData::getFieldValue(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in GoodsPricePercentData", fieldName.c_str());
	return "";
}

