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

std::string GameData::description() const
{
	std::string desc = "gameData = {\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tday : " + to_string(p_day) + "\n";
	desc += "}\n";
	return desc;
}

GameData* GameData::getSharedInstance()
{
	if (!p_sharedData) {
		p_sharedData = new GameData();
		static std::string resPath = "res/base/data/game.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			p_sharedData->p_year = buffer->getInt();
			p_sharedData->p_month = buffer->getInt();
			p_sharedData->p_day = buffer->getInt();
		}
	}
	return p_sharedData;
}

bool GameData::saveData(const std::string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putInt(3);
	buffer->putString("p_year");
	buffer->putString(to_string(data->p_year));
	buffer->putString("p_month");
	buffer->putString(to_string(data->p_month));
	buffer->putString("p_day");
	buffer->putString(to_string(data->p_day));
	buffer->writeToFile(filePath);
	return true;
}

bool GameData::loadData(const std::string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto dataSize = buffer->getInt();
		for (int j = 0; j < dataSize; ++j) {
			std::string key = buffer->getString();
			std::string value = buffer->getString();
			if (data != nullptr) {
				if (key == "p_year") {
					data->p_year = atoi(value.c_str());
				} else if (key == "p_month") {
					data->p_month = atoi(value.c_str());
				} else if (key == "p_day") {
					data->p_day = atoi(value.c_str());
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
