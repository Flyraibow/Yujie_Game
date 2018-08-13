/*
This file (CityBuildingData.cpp) is generated
*/
#include "CityBuildingData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

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

cocos2d::Sprite* CityBuildingData::getBuildingImage(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/cityBuilding/";
	string path = s_basePath + p_buildingImageId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string CityBuildingData::getBuildingImagePath()
{
	static const string s_basePath = "res/base/icon/cityBuilding/";
	return s_basePath + p_buildingImageId;
}

string CityBuildingData::getBuildingImageId() const
{
	return p_buildingImageId;
}

double CityBuildingData::getAnchorX() const
{
	return p_anchorX;
}

double CityBuildingData::getAnchorY() const
{
	return p_anchorY;
}

double CityBuildingData::getPosX() const
{
	return p_posX;
}

double CityBuildingData::getPosY() const
{
	return p_posY;
}

string CityBuildingData::description() const
{
	string desc = "cityBuildingData = {\n";
	desc += "\tbuildingId : " + to_string(p_buildingId) + "\n";
	desc += "\tbuildingName : " + getBuildingName() + "\n";
	desc += "\tbuildingImageId : " + to_string(p_buildingImageId) + "\n";
	desc += "\tanchorX : " + to_string(p_anchorX) + "\n";
	desc += "\tanchorY : " + to_string(p_anchorY) + "\n";
	desc += "\tposX : " + to_string(p_posX) + "\n";
	desc += "\tposY : " + to_string(p_posY) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, CityBuildingData*>* CityBuildingData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityBuildingData*>();
		static string resPath = "res/base/data/cityBuilding.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityBuildingData* cityBuildingData = new CityBuildingData();
				cityBuildingData->p_buildingId = buffer->getInt();
				cityBuildingData->p_buildingImageId = buffer->getString();
				cityBuildingData->p_anchorX = buffer->getDouble();
				cityBuildingData->p_anchorY = buffer->getDouble();
				cityBuildingData->p_posX = buffer->getDouble();
				cityBuildingData->p_posY = buffer->getDouble();
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

string CityBuildingData::getFieldValue(const string & fieldName)
{
	if (fieldName == "buildingId") {
		return to_string(this->getBuildingId());
	} else if (fieldName == "buildingName") {
		return to_string(this->getBuildingName());
	} else if (fieldName == "buildingImageId") {
		return to_string(this->getBuildingImageId());
	} else if (fieldName == "anchorX") {
		return to_string(this->getAnchorX());
	} else if (fieldName == "anchorY") {
		return to_string(this->getAnchorY());
	} else if (fieldName == "posX") {
		return to_string(this->getPosX());
	} else if (fieldName == "posY") {
		return to_string(this->getPosY());
	}
	CCLOGWARN("Couldn't recognize %s in CityBuildingData", fieldName.c_str());
	return "";
}

