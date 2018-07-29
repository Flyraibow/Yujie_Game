/*
This file (GameData.cpp) is generated
*/
#include "GameData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace std;

GameData* GameData::p_sharedData = nullptr;

int GameData::getYear() const
{
	return p_year;
}

void GameData::setYear(int year)
{
	p_year = year;
}

int GameData::getMonth() const
{
	return p_month;
}

void GameData::setMonth(int month)
{
	p_month = month;
}

int GameData::getDay() const
{
	return p_day;
}

void GameData::setDay(int day)
{
	p_day = day;
}

CityData* GameData::getCityIdData() const
{
	return CityData::getCityDataById(p_cityIdId);
}

string GameData::getCityIdId() const
{
	return p_cityIdId;
}

void GameData::setCityIdId(string cityId)
{
	p_cityIdId = cityId;
}

GuildData* GameData::getGuildIdData() const
{
	return GuildData::getGuildDataById(p_guildIdId);
}

string GameData::getGuildIdId() const
{
	return p_guildIdId;
}

void GameData::setGuildIdId(string guildId)
{
	p_guildIdId = guildId;
}

string GameData::description() const
{
	string desc = "gameData = {\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tday : " + to_string(p_day) + "\n";
	desc += "\tcityId : " + to_string(p_cityIdId) + "\n";
	desc += "\tguildId : " + to_string(p_guildIdId) + "\n";
	desc += "}\n";
	return desc;
}

GameData* GameData::getSharedInstance()
{
	if (!p_sharedData) {
		p_sharedData = new GameData();
		static string resPath = "res/base/data/game.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			p_sharedData->p_year = buffer->getInt();
			p_sharedData->p_month = buffer->getInt();
			p_sharedData->p_day = buffer->getInt();
			p_sharedData->p_cityIdId = buffer->getString();
			p_sharedData->p_guildIdId = buffer->getString();
		}
	}
	return p_sharedData;
}

bool GameData::saveData(const string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto buffer = make_unique<bb::ByteBuffer>();
	buffer->putInt(5);
	buffer->putString("p_year");
	buffer->putString(to_string(data->p_year));
	buffer->putString("p_month");
	buffer->putString(to_string(data->p_month));
	buffer->putString("p_day");
	buffer->putString(to_string(data->p_day));
	buffer->putString("p_cityIdId");
	buffer->putString(to_string(data->p_cityIdId));
	buffer->putString("p_guildIdId");
	buffer->putString(to_string(data->p_guildIdId));
	buffer->writeToFile(filePath);
	return true;
}

bool GameData::loadData(const string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto dataSize = buffer->getInt();
		for (int j = 0; j < dataSize; ++j) {
			string key = buffer->getString();
			string value = buffer->getString();
			if (data != nullptr) {
				if (key == "p_year") {
					data->p_year = atoi(value.c_str());
				} else if (key == "p_month") {
					data->p_month = atoi(value.c_str());
				} else if (key == "p_day") {
					data->p_day = atoi(value.c_str());
				} else if (key == "p_cityIdId") {
					data->p_cityIdId = value;
				} else if (key == "p_guildIdId") {
					data->p_guildIdId = value;
				}
			}
		}
	}
	return true;
}

bool GameData::clearData()
{
	if (p_sharedData != nullptr) {
		delete p_sharedData;
		p_sharedData = nullptr;
	}
	return true;
}

