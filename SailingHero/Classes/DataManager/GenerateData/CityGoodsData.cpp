/*
This file (CityGoodsData.cpp) is generated
*/
#include "CityGoodsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<int, CityGoodsData*>* CityGoodsData::p_sharedDictionary = nullptr;

string CityGoodsData::getId() const
{
	return to_string(p_cityGoodsId);
}

int CityGoodsData::getCityGoodsId() const
{
	return p_cityGoodsId;
}

GoodsData* CityGoodsData::getGoodsData() const
{
	return GoodsData::getGoodsDataById(p_goodsId);
}

string CityGoodsData::getGoodsId() const
{
	return p_goodsId;
}

int CityGoodsData::getCommercialRequirement() const
{
	return p_commercialRequirement;
}

int CityGoodsData::getBasePrice() const
{
	return p_basePrice;
}

int CityGoodsData::getAbundance() const
{
	return p_abundance;
}

void CityGoodsData::setAbundance(int abundance)
{
	p_abundance = abundance;
}

bool CityGoodsData::getIsHidden() const
{
	return p_isHidden;
}

void CityGoodsData::setIsHidden(bool isHidden)
{
	p_isHidden = isHidden;
}

string CityGoodsData::description() const
{
	string desc = "cityGoodsData = {\n";
	desc += "\tcityGoodsId : " + to_string(p_cityGoodsId) + "\n";
	desc += "\tgoods : " + to_string(p_goodsId) + "\n";
	desc += "\tcommercialRequirement : " + to_string(p_commercialRequirement) + "\n";
	desc += "\tbasePrice : " + to_string(p_basePrice) + "\n";
	desc += "\tabundance : " + to_string(p_abundance) + "\n";
	desc += "\tisHidden : " + to_string(p_isHidden) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, CityGoodsData*>* CityGoodsData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityGoodsData*>();
		static string resPath = "res/base/data/cityGoods.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityGoodsData* cityGoodsData = new CityGoodsData();
				cityGoodsData->p_cityGoodsId = buffer->getInt();
				cityGoodsData->p_goodsId = buffer->getString();
				cityGoodsData->p_commercialRequirement = buffer->getInt();
				cityGoodsData->p_basePrice = buffer->getInt();
				cityGoodsData->p_abundance = buffer->getInt();
				cityGoodsData->p_isHidden = buffer->getChar();
				p_sharedDictionary->insert(pair<int, CityGoodsData*>(cityGoodsData->p_cityGoodsId, cityGoodsData));
			}
		}
	}
	return p_sharedDictionary;
}

CityGoodsData* CityGoodsData::getCityGoodsDataById(int cityGoodsId)
{
	if (CityGoodsData::getSharedDictionary()->count(cityGoodsId)) {
		return CityGoodsData::getSharedDictionary()->at(cityGoodsId);
	}
	return nullptr;
}

CityGoodsData* CityGoodsData::getCityGoodsDataById(const string& cityGoodsId)
{
	if (cityGoodsId.length() == 0) return nullptr;
	return CityGoodsData::getCityGoodsDataById(atoi(cityGoodsId.c_str()));
}

bool CityGoodsData::saveData(const string & path)
{
	auto filePath = path + "/CityGoodsData.dat";
	auto dict = CityGoodsData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(2);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_abundance");
		buffer->putString(to_string(data->p_abundance));
		buffer->putString("p_isHidden");
		buffer->putString(to_string(data->p_isHidden));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool CityGoodsData::loadData(const string & path)
{
	auto filePath = path + "/CityGoodsData.dat";
	auto dict = CityGoodsData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			CityGoodsData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_abundance") {
						data->p_abundance = atoi(value.c_str());
					} else if (key == "p_isHidden") {
						data->p_isHidden = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool CityGoodsData::clearData()
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

