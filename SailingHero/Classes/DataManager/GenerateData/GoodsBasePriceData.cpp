/*
This file (GoodsBasePriceData.cpp) is generated
*/
#include "GoodsBasePriceData.hpp"
#include "ByteBuffer.hpp"



map<int, map<int,int>>* GoodsBasePriceData::p_sharedDictionary = nullptr;

const map<int, map<int,int>>* GoodsBasePriceData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, map<int,int>>();
		static string resPath = "res/base/data/goodsBasePrice.dat";
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

int GoodsBasePriceData::getGoodsBasePrice(int goodsId, int cultureId)
{
	auto dict = getSharedDictionary();
	if (dict->count(goodsId)) {
		if (dict->at(goodsId).count(cultureId)) {
			return dict->at(goodsId).at(cultureId);
		} else {
			CCLOGWARN("Couldn't find cultureId: %s in GoodsBasePrice", to_string(cultureId).c_str());
		}
	} else {
		CCLOGWARN("Couldn't find goodsId: %s in GoodsBasePrice", to_string(goodsId).c_str());
	}
	return 0;
}

string GoodsBasePriceData::getFieldValue(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in GoodsBasePriceData", fieldName.c_str());
	return "";
}

