/*
This file (GameData.cpp) is generated
*/
#include "GameData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

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

CityData* GameData::getCityData() const
{
	return CityData::getCityDataById(p_cityId);
}

string GameData::getCityId() const
{
	return p_cityId;
}

void GameData::setCityId(string city)
{
	p_cityId = city;
}

GuildData* GameData::getGuildData() const
{
	return GuildData::getGuildDataById(p_guildId);
}

string GameData::getGuildId() const
{
	return p_guildId;
}

void GameData::setGuildId(string guild)
{
	p_guildId = guild;
}

string GameData::description() const
{
	string desc = "gameData = {\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tday : " + to_string(p_day) + "\n";
	desc += "\tcity : " + to_string(p_cityId) + "\n";
	desc += "\tguild : " + to_string(p_guildId) + "\n";
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
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			p_sharedData->p_year = buffer->getInt();
			p_sharedData->p_month = buffer->getInt();
			p_sharedData->p_day = buffer->getInt();
			p_sharedData->p_cityId = buffer->getString();
			p_sharedData->p_guildId = buffer->getString();
		}
	}
	return p_sharedData;
}

bool GameData::saveData(const string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putInt(5);
	buffer->putString("p_year");
	buffer->putString(to_string(data->p_year));
	buffer->putString("p_month");
	buffer->putString(to_string(data->p_month));
	buffer->putString("p_day");
	buffer->putString(to_string(data->p_day));
	buffer->putString("p_cityId");
	buffer->putString(to_string(data->p_cityId));
	buffer->putString("p_guildId");
	buffer->putString(to_string(data->p_guildId));
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
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
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
				} else if (key == "p_cityId") {
					data->p_cityId = value;
				} else if (key == "p_guildId") {
					data->p_guildId = value;
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

void GameData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "year") {
		this->setYear(atoi(value.c_str()));
	} else if (fieldName == "month") {
		this->setMonth(atoi(value.c_str()));
	} else if (fieldName == "day") {
		this->setDay(atoi(value.c_str()));
	} else if (fieldName == "city") {
		this->setCityId(value);
	} else if (fieldName == "guild") {
		this->setGuildId(value);
	}
}

string GameData::getFieldValue(const string & fieldName)
{
	if (fieldName == "year") {
		return to_string(this->getYear());
	} else if (fieldName == "month") {
		return to_string(this->getMonth());
	} else if (fieldName == "day") {
		return to_string(this->getDay());
	} else if (fieldName == "city") {
		return to_string(this->getCityId());
	} else if (fieldName == "guild") {
		return to_string(this->getGuildId());
	}
	CCLOGWARN("Couldn't recognize %s in GameData", fieldName.c_str());
	return "";
}

