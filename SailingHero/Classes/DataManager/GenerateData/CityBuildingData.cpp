/*
This file (CityBuildingData.cpp) is generated
*/
#include "CityBuildingData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<int, CityBuildingData*>* CityBuildingData::p_sharedDictionary = nullptr;

string CityBuildingData::getId() const
{
	return to_string(p_buildingId);
}

int CityBuildingData::getBuildingId() const
{
	return p_buildingId;
}

string CityBuildingData::getBuildingName() const
{
	string localId = "cityBuilding_buildingName_" + to_string(p_buildingId);
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

map<int, CityBuildingData*>* CityBuildingData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityBuildingData*>();
		static string resPath = "res/base/data/cityBuilding.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityBuildingData* cityBuildingData = new CityBuildingData();
				cityBuildingData->p_buildingId = buffer->getInt();
				cityBuildingData->p_buildingImage = buffer->getString();
				p_sharedDictionary->insert(pair<int, CityBuildingData*>(cityBuildingData->p_buildingId, cityBuildingData));
			}
		}
	}
	return p_sharedDictionary;
}

CityBuildingData* CityBuildingData::getCityBuildingDataById(int buildingId)
{
	if (CityBuildingData::getSharedDictionary()->count(buildingId)) {
		return CityBuildingData::getSharedDictionary()->at(buildingId);
	}
	return nullptr;
}

CityBuildingData* CityBuildingData::getCityBuildingDataById(const string& buildingId)
{
	if (buildingId.length() == 0) return nullptr;
	return CityBuildingData::getCityBuildingDataById(atoi(buildingId.c_str()));
}

