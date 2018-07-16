/*
This file (CityBuildingData.cpp) is generated
*/
#include "CityBuildingData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, CityBuildingData*>* CityBuildingData::p_sharedDictionary = nullptr;

string CityBuildingData::getId() const
{
	return p_buildingId;
}

string CityBuildingData::getBuildingId() const
{
	return p_buildingId;
}

string CityBuildingData::getBuildingName() const
{
	string localId = "cityBuilding_buildingName_" + p_buildingId;
	return LocalizationHelper::getLocalization(localId);
}

string CityBuildingData::getBuildingImage() const
{
	return p_buildingImage;
}

string CityBuildingData::description() const
{
	string desc = "cityBuildingData = {\n";
	desc += "\tbuildingId : " + to_string(p_buildingId) + "\n";
	desc += "\tbuildingName : " + getBuildingName() + "\n";
	desc += "\tbuildingImage : " + to_string(p_buildingImage) + "\n";
	desc += "}\n";
	return desc;
}

map<string, CityBuildingData*>* CityBuildingData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CityBuildingData*>();
		static string resPath = "res/base/data/cityBuilding.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityBuildingData* cityBuildingData = new CityBuildingData();
				cityBuildingData->p_buildingId = buffer->getString();
				cityBuildingData->p_buildingImage = buffer->getString();
				p_sharedDictionary->insert(pair<string, CityBuildingData*>(cityBuildingData->p_buildingId, cityBuildingData));
			}
		}
	}
	return p_sharedDictionary;
}

CityBuildingData* CityBuildingData::getCityBuildingDataById(const string& buildingId)
{
	if (CityBuildingData::getSharedDictionary()->count(buildingId)) {
		return CityBuildingData::getSharedDictionary()->at(buildingId);
	}
	CCLOGERROR("invalid buildingId %s", buildingId.c_str());
	return nullptr;
}

