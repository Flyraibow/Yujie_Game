/*
This file (CityTypeData.cpp) is generated
*/
#include "CityTypeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, CityTypeData*>* CityTypeData::p_sharedDictionary = nullptr;

string CityTypeData::getId() const
{
	return p_cityTypeId;
}

string CityTypeData::getCityTypeId() const
{
	return p_cityTypeId;
}

string CityTypeData::getCityTypeName() const
{
	string localId = "cityType_cityTypeName_" + p_cityTypeId;
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

map<string, CityTypeData*>* CityTypeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CityTypeData*>();
		static string resPath = "res/base/data/cityType.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityTypeData* cityTypeData = new CityTypeData();
				cityTypeData->p_cityTypeId = buffer->getString();
				p_sharedDictionary->insert(pair<string, CityTypeData*>(cityTypeData->p_cityTypeId, cityTypeData));
			}
		}
	}
	return p_sharedDictionary;
}

CityTypeData* CityTypeData::getCityTypeDataById(const string& cityTypeId)
{
	if (CityTypeData::getSharedDictionary()->count(cityTypeId)) {
		return CityTypeData::getSharedDictionary()->at(cityTypeId);
	}
	CCLOGERROR("invalid cityTypeId %s", cityTypeId.c_str());
	return nullptr;
}

