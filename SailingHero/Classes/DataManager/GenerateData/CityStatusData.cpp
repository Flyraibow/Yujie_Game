/*
This file (CityStatusData.cpp) is generated
*/
#include "CityStatusData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, CityStatusData*>* CityStatusData::p_sharedDictionary = nullptr;

string CityStatusData::getId() const
{
	return p_cityStatusId;
}

string CityStatusData::getCityStatusId() const
{
	return p_cityStatusId;
}

string CityStatusData::getCityStatusName() const
{
	string localId = "cityStatus_cityStatusName_" + p_cityStatusId;
	return LocalizationHelper::getLocalization(localId);
}

string CityStatusData::description() const
{
	string desc = "cityStatusData = {\n";
	desc += "\tcityStatusId : " + to_string(p_cityStatusId) + "\n";
	desc += "\tcityStatusName : " + getCityStatusName() + "\n";
	desc += "}\n";
	return desc;
}

map<string, CityStatusData*>* CityStatusData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CityStatusData*>();
		static string resPath = "res/base/data/cityStatus.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityStatusData* cityStatusData = new CityStatusData();
				cityStatusData->p_cityStatusId = buffer->getString();
				p_sharedDictionary->insert(pair<string, CityStatusData*>(cityStatusData->p_cityStatusId, cityStatusData));
			}
		}
	}
	return p_sharedDictionary;
}

CityStatusData* CityStatusData::getCityStatusDataById(const string& cityStatusId)
{
	if (CityStatusData::getSharedDictionary()->count(cityStatusId)) {
		return CityStatusData::getSharedDictionary()->at(cityStatusId);
	}
	if (cityStatusId.length() > 0) {
		CCLOGWARN("invalid cityStatusId %s", cityStatusId.c_str());
	}
	return nullptr;
}

