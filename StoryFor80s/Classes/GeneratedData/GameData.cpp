/*
This file (GameData.cpp) is generated
*/
#include "GameData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

GameData* GameData::p_sharedData = nullptr;

DateData* GameData::getGameDateData() const
{
	return DateData::getDateDataById(p_gameDateId);
}

string GameData::getGameDateId() const
{
	return p_gameDateId;
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

DateData* GameData::getMyBirthDayData() const
{
	return DateData::getDateDataById(p_myBirthDayId);
}

string GameData::getMyBirthDayId() const
{
	return p_myBirthDayId;
}

FatherJobData* GameData::getParentJobData() const
{
	return FatherJobData::getFatherJobDataById(p_parentJobId);
}

string GameData::getParentJobId() const
{
	return p_parentJobId;
}

void GameData::setParentJobId(string parentJob)
{
	p_parentJobId = parentJob;
}

SchoolData* GameData::getSchoolData() const
{
	return SchoolData::getSchoolDataById(p_schoolId);
}

string GameData::getSchoolId() const
{
	return p_schoolId;
}

void GameData::setSchoolId(string school)
{
	p_schoolId = school;
}

bool GameData::getHasTalkedToParent() const
{
	return p_hasTalkedToParent;
}

void GameData::setHasTalkedToParent(bool hasTalkedToParent)
{
	p_hasTalkedToParent = hasTalkedToParent;
}

string GameData::description() const
{
	string desc = "gameData = {\n";
	desc += "\tgameDate : " + to_string(p_gameDateId) + "\n";
	desc += "\tfirstName : " + to_string(p_firstName) + "\n";
	desc += "\tlastName : " + to_string(p_lastName) + "\n";
	desc += "\tmyBirthDay : " + to_string(p_myBirthDayId) + "\n";
	desc += "\tparentJob : " + to_string(p_parentJobId) + "\n";
	desc += "\tschool : " + to_string(p_schoolId) + "\n";
	desc += "\thasTalkedToParent : " + to_string(p_hasTalkedToParent) + "\n";
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
			p_sharedData->p_gameDateId = buffer->getString();
			p_sharedData->p_firstName = buffer->getString();
			p_sharedData->p_lastName = buffer->getString();
			p_sharedData->p_myBirthDayId = buffer->getString();
			p_sharedData->p_parentJobId = buffer->getString();
			p_sharedData->p_schoolId = buffer->getString();
			p_sharedData->p_hasTalkedToParent = buffer->getChar();
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
	buffer->putString("p_firstName");
	buffer->putString(to_string(data->p_firstName));
	buffer->putString("p_lastName");
	buffer->putString(to_string(data->p_lastName));
	buffer->putString("p_parentJobId");
	buffer->putString(to_string(data->p_parentJobId));
	buffer->putString("p_schoolId");
	buffer->putString(to_string(data->p_schoolId));
	buffer->putString("p_hasTalkedToParent");
	buffer->putString(to_string(data->p_hasTalkedToParent));
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
				if (key == "p_firstName") {
					data->p_firstName = value;
				} else if (key == "p_lastName") {
					data->p_lastName = value;
				} else if (key == "p_parentJobId") {
					data->p_parentJobId = value;
				} else if (key == "p_schoolId") {
					data->p_schoolId = value;
				} else if (key == "p_hasTalkedToParent") {
					data->p_hasTalkedToParent = (atoi(value.c_str()) != 0);
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
	if (fieldName == "firstName") {
		this->setFirstName(value);
	} else if (fieldName == "lastName") {
		this->setLastName(value);
	} else if (fieldName == "parentJob") {
		this->setParentJobId(value);
	} else if (fieldName == "school") {
		this->setSchoolId(value);
	} else if (fieldName == "hasTalkedToParent") {
		this->setHasTalkedToParent((atoi(value.c_str()) != 0));
	}
}

string GameData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "gameDate") {
		return to_string(this->getGameDateId());
	} else if (fieldName == "firstName") {
		return to_string(this->getFirstName());
	} else if (fieldName == "lastName") {
		return to_string(this->getLastName());
	} else if (fieldName == "myBirthDay") {
		return to_string(this->getMyBirthDayId());
	} else if (fieldName == "parentJob") {
		return to_string(this->getParentJobId());
	} else if (fieldName == "school") {
		return to_string(this->getSchoolId());
	} else if (fieldName == "hasTalkedToParent") {
		return to_string(this->getHasTalkedToParent());
	}
	CCLOGWARN("Couldn't recognize %s in GameData", fieldName.c_str());
	return "";
}

BaseData* GameData::getDataByField(const string & fieldName) const
{
	if (fieldName == "gameDate") {
		return this->getGameDateData();
	} else if (fieldName == "myBirthDay") {
		return this->getMyBirthDayData();
	} else if (fieldName == "parentJob") {
		return this->getParentJobData();
	} else if (fieldName == "school") {
		return this->getSchoolData();
	}
	CCLOGWARN("Couldn't recognize %s in GameData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> GameData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in GameData", fieldName.c_str());
	return vector<BaseData *>();
}

