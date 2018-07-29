/*
This file (CityStatusData.cpp) is generated
*/
#include "CityStatusData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, CityStatusData*>* CityStatusData::p_sharedDictionary = nullptr;

string CityStatusData::getId() const
{
	return to_string(p_cityStatusId);
}

int CityStatusData::getCityStatusId() const
{
	return p_cityStatusId;
}

string CityStatusData::getCityStatusName() const
{
	string localId = "cityStatus_cityStatusName_" + to_string(p_cityStatusId);
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

map<int, CityStatusData*>* CityStatusData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityStatusData*>();
		static string resPath = "res/base/data/cityStatus.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityStatusData* cityStatusData = new CityStatusData();
				cityStatusData->p_cityStatusId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, CityStatusData*>(cityStatusData->p_cityStatusId, cityStatusData));
			}
		}
	}
	return p_sharedDictionary;
}

CityStatusData* CityStatusData::getCityStatusDataById(int cityStatusId)
{
	if (CityStatusData::getSharedDictionary()->count(cityStatusId)) {
		return CityStatusData::getSharedDictionary()->at(cityStatusId);
	}
	return nullptr;
}

CityStatusData* CityStatusData::getCityStatusDataById(const string& cityStatusId)
{
	if (cityStatusId.length() == 0) return nullptr;
	return CityStatusData::getCityStatusDataById(atoi(cityStatusId.c_str()));
}

