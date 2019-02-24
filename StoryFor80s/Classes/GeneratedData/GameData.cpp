/*
This file (GameData.cpp) is generated
*/
#include "GameData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

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

string GameData::getFirstName() const
{
	return p_firstName;
}

void GameData::setFirstName(string firstName)
{
	p_firstName = firstName;
}

string GameData::getLastName() const
{
	return p_lastName;
}

void GameData::setLastName(string lastName)
{
	p_lastName = lastName;
}

int GameData::getBirthDay() const
{
	return p_birthDay;
}

void GameData::setBirthDay(int birthDay)
{
	p_birthDay = birthDay;
}

int GameData::getBirthMonth() const
{
	return p_birthMonth;
}

void GameData::setBirthMonth(int birthMonth)
{
	p_birthMonth = birthMonth;
}

int GameData::getBirthYear() const
{
	return p_birthYear;
}

void GameData::setBirthYear(int birthYear)
{
	p_birthYear = birthYear;
}

string GameData::description() const
{
	string desc = "gameData = {\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tday : " + to_string(p_day) + "\n";
	desc += "\tfirstName : " + to_string(p_firstName) + "\n";
	desc += "\tlastName : " + to_string(p_lastName) + "\n";
	desc += "\tbirthDay : " + to_string(p_birthDay) + "\n";
	desc += "\tbirthMonth : " + to_string(p_birthMonth) + "\n";
	desc += "\tbirthYear : " + to_string(p_birthYear) + "\n";
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
			p_sharedData->p_firstName = buffer->getString();
			p_sharedData->p_lastName = buffer->getString();
			p_sharedData->p_birthDay = buffer->getInt();
			p_sharedData->p_birthMonth = buffer->getInt();
			p_sharedData->p_birthYear = buffer->getInt();
		}
	}
	return p_sharedData;
}

bool GameData::saveData(const string & path)
{
	auto filePath = path + "/GameData.dat";
	auto data = GameData::getSharedInstance();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putInt(8);
	buffer->putString("p_year");
	buffer->putString(to_string(data->p_year));
	buffer->putString("p_month");
	buffer->putString(to_string(data->p_month));
	buffer->putString("p_day");
	buffer->putString(to_string(data->p_day));
	buffer->putString("p_firstName");
	buffer->putString(to_string(data->p_firstName));
	buffer->putString("p_lastName");
	buffer->putString(to_string(data->p_lastName));
	buffer->putString("p_birthDay");
	buffer->putString(to_string(data->p_birthDay));
	buffer->putString("p_birthMonth");
	buffer->putString(to_string(data->p_birthMonth));
	buffer->putString("p_birthYear");
	buffer->putString(to_string(data->p_birthYear));
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
				} else if (key == "p_firstName") {
					data->p_firstName = value;
				} else if (key == "p_lastName") {
					data->p_lastName = value;
				} else if (key == "p_birthDay") {
					data->p_birthDay = atoi(value.c_str());
				} else if (key == "p_birthMonth") {
					data->p_birthMonth = atoi(value.c_str());
				} else if (key == "p_birthYear") {
					data->p_birthYear = atoi(value.c_str());
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
	} else if (fieldName == "firstName") {
		this->setFirstName(value);
	} else if (fieldName == "lastName") {
		this->setLastName(value);
	} else if (fieldName == "birthDay") {
		this->setBirthDay(atoi(value.c_str()));
	} else if (fieldName == "birthMonth") {
		this->setBirthMonth(atoi(value.c_str()));
	} else if (fieldName == "birthYear") {
		this->setBirthYear(atoi(value.c_str()));
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
	} else if (fieldName == "firstName") {
		return to_string(this->getFirstName());
	} else if (fieldName == "lastName") {
		return to_string(this->getLastName());
	} else if (fieldName == "birthDay") {
		return to_string(this->getBirthDay());
	} else if (fieldName == "birthMonth") {
		return to_string(this->getBirthMonth());
	} else if (fieldName == "birthYear") {
		return to_string(this->getBirthYear());
	}
	CCLOGWARN("Couldn't recognize %s in GameData", fieldName.c_str());
	return "";
}

