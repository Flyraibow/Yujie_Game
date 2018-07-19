/*
This file (CityData.cpp) is generated
*/
#include "CityData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace std;

map<int, CityData*>* CityData::p_sharedDictionary = nullptr;

string CityData::getId() const
{
	return to_string(p_cityId);
}

int CityData::getCityId() const
{
	return p_cityId;
}

void CityData::setCityName(string cityName)
{
	p_cityName = cityName;
}

string CityData::getCityName() const
{
	if (p_cityName.length() > 0) {
		return p_cityName;
	}
	string localId = "city_cityName_" + to_string(p_cityId);
	return LocalizationHelper::getLocalization(localId);
}

CultureData* CityData::getCultureData() const
{
	return CultureData::getCultureDataById(p_cultureId);
}

string CityData::getCultureId() const
{
	return p_cultureId;
}

CityStatusData* CityData::getCityStatusData() const
{
	return CityStatusData::getCityStatusDataById(p_cityStatusId);
}

string CityData::getCityStatusId() const
{
	return p_cityStatusId;
}

void CityData::setCityStatusId(string cityStatus)
{
	p_cityStatusId = cityStatus;
}

CityTypeData* CityData::getCityTypeData() const
{
	return CityTypeData::getCityTypeDataById(p_cityTypeId);
}

string CityData::getCityTypeId() const
{
	return p_cityTypeId;
}

double CityData::getLongitude() const
{
	return p_longitude;
}

double CityData::getLatitude() const
{
	return p_latitude;
}

int CityData::getCommerce() const
{
	return p_commerce;
}

void CityData::setCommerce(int commerce)
{
	p_commerce = commerce;
}

int CityData::getMilltary() const
{
	return p_milltary;
}

void CityData::setMilltary(int milltary)
{
	p_milltary = milltary;
}

map<string, int> CityData::getGuildShareMap() const
{
	return p_guildShareMap;
}

void CityData::setGuildShareMap(map<string, int> guildShare)
{
	p_guildShareMap = guildShare;
}

vector<CityGoodsData*> CityData::getCityGoodsDataVector() const
{
	vector<CityGoodsData*> resultVector;
	for (auto objId : p_cityGoodsIdVector) {
		resultVector.push_back(CityGoodsData::getCityGoodsDataById(objId));
	}
	return resultVector;
}

vector<string> CityData::getCityGoodsIdVector() const
{
	return p_cityGoodsIdVector;
}

set<CityBuildingData*> CityData::getBuildingDataSet() const
{
	set<CityBuildingData*> resultSet;
	for (auto objId : p_buildingIdSet) {
		resultSet.insert(CityBuildingData::getCityBuildingDataById(objId));
	}
	return resultSet;
}

set<string> CityData::getBuildingIdSet() const
{
	return p_buildingIdSet;
}

void CityData::setBuildingIdSet(set<string> building)
{
	p_buildingIdSet = building;
}

string CityData::description() const
{
	string desc = "cityData = {\n";
	desc += "\tcityId : " + to_string(p_cityId) + "\n";
	desc += "\tcityName : " + getCityName() + "\n";
	desc += "\tculture : " + to_string(p_cultureId) + "\n";
	desc += "\tcityStatus : " + to_string(p_cityStatusId) + "\n";
	desc += "\tcityType : " + to_string(p_cityTypeId) + "\n";
	desc += "\tlongitude : " + to_string(p_longitude) + "\n";
	desc += "\tlatitude : " + to_string(p_latitude) + "\n";
	desc += "\tcommerce : " + to_string(p_commerce) + "\n";
	desc += "\tmilltary : " + to_string(p_milltary) + "\n";
	
	desc += "\tguildShare : " + to_string(p_guildShareMap)+ "\n";
	desc += "\tcityGoods : " + to_string(p_cityGoodsIdVector) + "\n";
	desc += "\tbuilding : " + to_string(p_buildingIdSet) + "\n";
	desc += "}\n";
	return desc;
}

map<int, CityData*>* CityData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CityData*>();
		static string resPath = "res/base/data/city.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CityData* cityData = new CityData();
				cityData->p_cityId = buffer->getInt();
				cityData->p_cultureId = buffer->getString();
				cityData->p_cityStatusId = buffer->getString();
				cityData->p_cityTypeId = buffer->getString();
				cityData->p_longitude = buffer->getDouble();
				cityData->p_latitude = buffer->getDouble();
				cityData->p_commerce = buffer->getInt();
				cityData->p_milltary = buffer->getInt();
				auto guildShareCount = buffer->getLong();
				for (int j = 0; j < guildShareCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					cityData->p_guildShareMap.insert(make_pair(key, val));
				}
				auto cityGoodsCount = buffer->getLong();
				for (int j = 0; j < cityGoodsCount; ++j) {
					cityData->p_cityGoodsIdVector.push_back(buffer->getString());
				}
				auto buildingCount = buffer->getLong();
				for (int j = 0; j < buildingCount; ++j) {
					cityData->p_buildingIdSet.insert(buffer->getString());
				}
				p_sharedDictionary->insert(pair<int, CityData*>(cityData->p_cityId, cityData));
			}
		}
	}
	return p_sharedDictionary;
}

CityData* CityData::getCityDataById(int cityId)
{
	if (CityData::getSharedDictionary()->count(cityId)) {
		return CityData::getSharedDictionary()->at(cityId);
	}
	return nullptr;
}

CityData* CityData::getCityDataById(const string& cityId)
{
	if (cityId.length() == 0) return nullptr;
	return CityData::getCityDataById(atoi(cityId.c_str()));
}

bool CityData::saveData(const string & path)
{
	auto filePath = path + "/CityData.dat";
	auto dict = CityData::getSharedDictionary();
	auto buffer = make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(6);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_cityName");
		buffer->putString(to_string(data->p_cityName));
		buffer->putString("p_cityStatusId");
		buffer->putString(to_string(data->p_cityStatusId));
		buffer->putString("p_commerce");
		buffer->putString(to_string(data->p_commerce));
		buffer->putString("p_milltary");
		buffer->putString(to_string(data->p_milltary));
		buffer->putString("p_guildShareMap");
		buffer->putString(to_string(data->p_guildShareMap));
		buffer->putString("p_buildingIdSet");
		buffer->putString(to_string(data->p_buildingIdSet));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool CityData::loadData(const string & path)
{
	auto filePath = path + "/CityData.dat";
	auto dict = CityData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			CityData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_cityName") {
						data->p_cityName = value;
					} else if (key == "p_cityStatusId") {
						data->p_cityStatusId = value;
					} else if (key == "p_commerce") {
						data->p_commerce = atoi(value.c_str());
					} else if (key == "p_milltary") {
						data->p_milltary = atoi(value.c_str());
					} else if (key == "p_guildShareMap") {
						map<string, int> guildShareMap;
						auto guildShareList = atomap(value);
						for (auto mapData : guildShareList) {
							guildShareMap.insert(make_pair(mapData.first, atoi(mapData.second.c_str())));
						}
						data->p_guildShareMap = guildShareMap;
					} else if (key == "p_buildingIdSet") {
						data->p_buildingIdSet = atoset(value);
					}
				}
			}
		}
	}
	return true;
}

bool CityData::clearData()
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

