/*
This file (ShipData.cpp) is generated
*/
#include "ShipData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ShipData*>* ShipData::p_sharedDictionary = nullptr;

string ShipData::getId() const
{
	return to_string(p_shipId);
}

int ShipData::getShipId() const
{
	return p_shipId;
}

void ShipData::setShipId(int shipId)
{
	p_shipId = shipId;
}

void ShipData::setShipName(string shipName)
{
	p_shipName = shipName;
}

string ShipData::getShipName() const
{
	if (p_shipName.length() > 0) {
		return p_shipName;
	}
	string localId = "ship_shipName_" + to_string(p_shipId);
	return LocalizationHelper::getLocalization(localId);
}

ShipStyleData* ShipData::getShipStyleData() const
{
	return ShipStyleData::getShipStyleDataById(p_shipStyleId);
}

string ShipData::getShipStyleId() const
{
	return p_shipStyleId;
}

CannonData* ShipData::getCannonData() const
{
	return CannonData::getCannonDataById(p_cannonId);
}

string ShipData::getCannonId() const
{
	return p_cannonId;
}

void ShipData::setCannonId(string cannon)
{
	p_cannonId = cannon;
}

int ShipData::getCurrentDuration() const
{
	return p_currentDuration;
}

void ShipData::setCurrentDuration(int currentDuration)
{
	p_currentDuration = currentDuration;
}

HeroData* ShipData::getLeaderData() const
{
	return HeroData::getHeroDataById(p_leaderId);
}

string ShipData::getLeaderId() const
{
	return p_leaderId;
}

void ShipData::setLeaderId(string leader)
{
	p_leaderId = leader;
}

string ShipData::description() const
{
	string desc = "shipData = {\n";
	desc += "\tshipId : " + to_string(p_shipId) + "\n";
	desc += "\tshipName : " + getShipName() + "\n";
	desc += "\tshipStyle : " + to_string(p_shipStyleId) + "\n";
	desc += "\tcannon : " + to_string(p_cannonId) + "\n";
	desc += "\tcurrentDuration : " + to_string(p_currentDuration) + "\n";
	desc += "\tleader : " + to_string(p_leaderId) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, ShipData*>* ShipData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ShipData*>();
		static string resPath = "res/base/data/ship.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ShipData* shipData = new ShipData();
				shipData->p_shipId = buffer->getInt();
				shipData->p_shipStyleId = buffer->getString();
				shipData->p_cannonId = buffer->getString();
				shipData->p_currentDuration = buffer->getInt();
				shipData->p_leaderId = buffer->getString();
				p_sharedDictionary->insert(pair<int, ShipData*>(shipData->p_shipId, shipData));
			}
		}
	}
	return p_sharedDictionary;
}

ShipData* ShipData::getShipDataById(int shipId)
{
	if (ShipData::getSharedDictionary()->count(shipId)) {
		return ShipData::getSharedDictionary()->at(shipId);
	}
	return nullptr;
}

ShipData* ShipData::getShipDataById(const string& shipId)
{
	if (shipId.length() == 0) return nullptr;
	return ShipData::getShipDataById(atoi(shipId.c_str()));
}

ShipData* ShipData::registerShipData(string shipName, string shipStyle, string cannon, int currentDuration, string leader)
{
	if (!getSharedDictionary()) {
		return nullptr;
	}
	int maxId = 0;
	if (p_sharedDictionary->size() > 0) {
		for (auto iter : *p_sharedDictionary) {
			if (iter.first >= maxId) {
				maxId = iter.first + 1;
			}
		}
	}
	auto data = new ShipData();
	data->p_shipId = maxId;
	data->p_shipName = shipName;
	data->p_shipStyleId = shipStyle;
	data->p_cannonId = cannon;
	data->p_currentDuration = currentDuration;
	data->p_leaderId = leader;
	p_sharedDictionary->insert(make_pair(maxId, data));
	return data;
}

bool ShipData::removeShipDataById(int shipId)
{
	if (getSharedDictionary() != nullptr && p_sharedDictionary->count(shipId)) {
		p_sharedDictionary->erase(shipId);
		return true;
	}
	return false;
}

bool ShipData::saveData(const string & path)
{
	auto filePath = path + "/ShipData.dat";
	auto dict = ShipData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(4);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_shipName");
		buffer->putString(to_string(data->p_shipName));
		buffer->putString("p_cannonId");
		buffer->putString(to_string(data->p_cannonId));
		buffer->putString("p_currentDuration");
		buffer->putString(to_string(data->p_currentDuration));
		buffer->putString("p_leaderId");
		buffer->putString(to_string(data->p_leaderId));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool ShipData::loadData(const string & path)
{
	auto filePath = path + "/ShipData.dat";
	auto dict = ShipData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			ShipData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_shipName") {
						data->p_shipName = value;
					} else if (key == "p_cannonId") {
						data->p_cannonId = value;
					} else if (key == "p_currentDuration") {
						data->p_currentDuration = atoi(value.c_str());
					} else if (key == "p_leaderId") {
						data->p_leaderId = value;
					}
				}
			}
		}
	}
	return true;
}

bool ShipData::clearData()
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

