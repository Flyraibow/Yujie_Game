/*
This file (ShipTeamData.cpp) is generated
*/
#include "ShipTeamData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "CityData.hpp"


using namespace SHUtil;

map<int, ShipTeamData*>* ShipTeamData::p_sharedDictionary = nullptr;

string ShipTeamData::getId() const
{
	return to_string(p_shipTeamId);
}

int ShipTeamData::getShipTeamId() const
{
	return p_shipTeamId;
}

HeroData* ShipTeamData::getLeaderData() const
{
	return HeroData::getHeroDataById(p_leaderId);
}

string ShipTeamData::getLeaderId() const
{
	return p_leaderId;
}

bool ShipTeamData::getIsActive() const
{
	return p_isActive;
}

void ShipTeamData::setIsActive(bool isActive)
{
	p_isActive = isActive;
}

bool ShipTeamData::getIsDismissed() const
{
	return p_isDismissed;
}

void ShipTeamData::setIsDismissed(bool isDismissed)
{
	p_isDismissed = isDismissed;
}

bool ShipTeamData::getHasInformation() const
{
	return p_hasInformation;
}

void ShipTeamData::setHasInformation(bool hasInformation)
{
	p_hasInformation = hasInformation;
}

bool ShipTeamData::getHasMet() const
{
	return p_hasMet;
}

void ShipTeamData::setHasMet(bool hasMet)
{
	p_hasMet = hasMet;
}

vector<ShipData*> ShipTeamData::getShipDataVector() const
{
	vector<ShipData*> resultVector;
	for (auto objId : p_shipIdVector) {
		resultVector.push_back(ShipData::getShipDataById(objId));
	}
	return resultVector;
}

vector<string> ShipTeamData::getShipIdVector() const
{
	return p_shipIdVector;
}

void ShipTeamData::setShipIdVector(vector<string> ship)
{
	p_shipIdVector = ship;
}

bool ShipTeamData::getIsOut() const
{
	return p_isOut;
}

void ShipTeamData::setIsOut(bool isOut)
{
	p_isOut = isOut;
}

double ShipTeamData::getPosX() const
{
	return p_posX;
}

void ShipTeamData::setPosX(double posX)
{
	p_posX = posX;
}

double ShipTeamData::getPosY() const
{
	return p_posY;
}

void ShipTeamData::setPosY(double posY)
{
	p_posY = posY;
}

CityData* ShipTeamData::getCityData() const
{
	return CityData::getCityDataById(p_cityId);
}

string ShipTeamData::getCityId() const
{
	return p_cityId;
}

void ShipTeamData::setCityId(string city)
{
	p_cityId = city;
}

int ShipTeamData::getTireness() const
{
	return p_tireness;
}

void ShipTeamData::setTireness(int tireness)
{
	p_tireness = tireness;
}

string ShipTeamData::description() const
{
	string desc = "shipTeamData = {\n";
	desc += "\tshipTeamId : " + to_string(p_shipTeamId) + "\n";
	desc += "\tleader : " + to_string(p_leaderId) + "\n";
	desc += "\tisActive : " + to_string(p_isActive) + "\n";
	desc += "\tisDismissed : " + to_string(p_isDismissed) + "\n";
	desc += "\thasInformation : " + to_string(p_hasInformation) + "\n";
	desc += "\thasMet : " + to_string(p_hasMet) + "\n";
	desc += "\tship : " + to_string(p_shipIdVector) + "\n";
	desc += "\tisOut : " + to_string(p_isOut) + "\n";
	desc += "\tposX : " + to_string(p_posX) + "\n";
	desc += "\tposY : " + to_string(p_posY) + "\n";
	desc += "\tcity : " + to_string(p_cityId) + "\n";
	desc += "\ttireness : " + to_string(p_tireness) + "\n";
	desc += "}\n";
	return desc;
}

map<int, ShipTeamData*>* ShipTeamData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ShipTeamData*>();
		static string resPath = "res/base/data/shipTeam.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ShipTeamData* shipTeamData = new ShipTeamData();
				shipTeamData->p_shipTeamId = buffer->getInt();
				shipTeamData->p_leaderId = buffer->getString();
				shipTeamData->p_isActive = buffer->getChar();
				shipTeamData->p_isDismissed = buffer->getChar();
				shipTeamData->p_hasInformation = buffer->getChar();
				shipTeamData->p_hasMet = buffer->getChar();
				auto shipCount = buffer->getLong();
				for (int j = 0; j < shipCount; ++j) {
					shipTeamData->p_shipIdVector.push_back(buffer->getString());
				}
				shipTeamData->p_isOut = buffer->getChar();
				shipTeamData->p_posX = buffer->getDouble();
				shipTeamData->p_posY = buffer->getDouble();
				shipTeamData->p_cityId = buffer->getString();
				shipTeamData->p_tireness = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ShipTeamData*>(shipTeamData->p_shipTeamId, shipTeamData));
			}
		}
	}
	return p_sharedDictionary;
}

ShipTeamData* ShipTeamData::getShipTeamDataById(int shipTeamId)
{
	if (ShipTeamData::getSharedDictionary()->count(shipTeamId)) {
		return ShipTeamData::getSharedDictionary()->at(shipTeamId);
	}
	return nullptr;
}

ShipTeamData* ShipTeamData::getShipTeamDataById(const string& shipTeamId)
{
	if (shipTeamId.length() == 0) return nullptr;
	return ShipTeamData::getShipTeamDataById(atoi(shipTeamId.c_str()));
}

bool ShipTeamData::saveData(const string & path)
{
	auto filePath = path + "/ShipTeamData.dat";
	auto dict = ShipTeamData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(10);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_isActive");
		buffer->putString(to_string(data->p_isActive));
		buffer->putString("p_isDismissed");
		buffer->putString(to_string(data->p_isDismissed));
		buffer->putString("p_hasInformation");
		buffer->putString(to_string(data->p_hasInformation));
		buffer->putString("p_hasMet");
		buffer->putString(to_string(data->p_hasMet));
		buffer->putString("p_shipIdVector");
		buffer->putString(to_string(data->p_shipIdVector));
		buffer->putString("p_isOut");
		buffer->putString(to_string(data->p_isOut));
		buffer->putString("p_posX");
		buffer->putString(to_string(data->p_posX));
		buffer->putString("p_posY");
		buffer->putString(to_string(data->p_posY));
		buffer->putString("p_cityId");
		buffer->putString(to_string(data->p_cityId));
		buffer->putString("p_tireness");
		buffer->putString(to_string(data->p_tireness));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool ShipTeamData::loadData(const string & path)
{
	auto filePath = path + "/ShipTeamData.dat";
	auto dict = ShipTeamData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			ShipTeamData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_isActive") {
						data->p_isActive = (atoi(value.c_str()) != 0);
					} else if (key == "p_isDismissed") {
						data->p_isDismissed = (atoi(value.c_str()) != 0);
					} else if (key == "p_hasInformation") {
						data->p_hasInformation = (atoi(value.c_str()) != 0);
					} else if (key == "p_hasMet") {
						data->p_hasMet = (atoi(value.c_str()) != 0);
					} else if (key == "p_shipIdVector") {
						data->p_shipIdVector = atovector(value);
					} else if (key == "p_isOut") {
						data->p_isOut = (atoi(value.c_str()) != 0);
					} else if (key == "p_posX") {
						data->p_posX = atof(value.c_str());
					} else if (key == "p_posY") {
						data->p_posY = atof(value.c_str());
					} else if (key == "p_cityId") {
						data->p_cityId = value;
					} else if (key == "p_tireness") {
						data->p_tireness = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool ShipTeamData::clearData()
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

