/*
This file (CityTypeData.cpp) is generated
*/
#include "CityTypeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, CityTypeData*>* CityTypeData::p_sharedDictionary = nullptr;

string CityTypeData::getId() const
{
	return to_string(p_cityTypeId);
}

int CityTypeData::getCityTypeId() const
{
	return p_cityTypeId;
}

string CityTypeData::getCityTypeName() const
{
	string localId = "cityType_cityTypeName_" + to_string(p_cityTypeId);
	return LocalizationHelper::getLocalization(localId);
}

string CityTypeData::description() const
{
	string desc = "cityTypeData = {\n";
	desc += "\tcityTypeId : " + to_string(p_cityTypeId) + "\n";
	desc += "\tcityTypeName : " + getCityTypeName() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, CityTypeData*>* CityTypeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityTypeData*>();
		static string resPath = "res/base/data/cityType.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityTypeData* cityTypeData = new CityTypeData();
				cityTypeData->p_cityTypeId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, CityTypeData*>(cityTypeData->p_cityTypeId, cityTypeData));
			}
		}
	}
	return p_sharedDictionary;
}

CityTypeData* CityTypeData::getCityTypeDataById(int cityTypeId)
{
	if (CityTypeData::getSharedDictionary()->count(cityTypeId)) {
		return CityTypeData::getSharedDictionary()->at(cityTypeId);
	}
	return nullptr;
}

CityTypeData* CityTypeData::getCityTypeDataById(const string& cityTypeId)
{
	if (cityTypeId.length() == 0) return nullptr;
	return CityTypeData::getCityTypeDataById(atoi(cityTypeId.c_str()));
}

