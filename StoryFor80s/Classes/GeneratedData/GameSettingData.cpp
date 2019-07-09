/*
This file (GameSettingData.cpp) is generated
*/
#include "GameSettingData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

GameSettingData* GameSettingData::p_sharedData = nullptr;

int GameSettingData::getSoundVolume() const
{
	return p_soundVolume;
}

void GameSettingData::setSoundVolume(int soundVolume)
{
	p_soundVolume = soundVolume;
}

int GameSettingData::getEffectVolume() const
{
	return p_effectVolume;
}

void GameSettingData::setEffectVolume(int effectVolume)
{
	p_effectVolume = effectVolume;
}

string GameSettingData::description() const
{
	string desc = "gameSettingData = {\n";
	desc += "\tsoundVolume : " + to_string(p_soundVolume) + "\n";
	desc += "\teffectVolume : " + to_string(p_effectVolume) + "\n";
	desc += "}\n";
	return desc;
}

GameSettingData* GameSettingData::getSharedInstance()
{
	if (!p_sharedData) {
		p_sharedData = new GameSettingData();
		static string resPath = "res/base/data/gameSetting.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			p_sharedData->p_soundVolume = buffer->getInt();
			p_sharedData->p_effectVolume = buffer->getInt();
		}
	}
	return p_sharedData;
}

bool GameSettingData::saveData(const string & path)
{
	auto filePath = path + "/GameSettingData.dat";
	auto data = GameSettingData::getSharedInstance();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putInt(2);
	buffer->putString("p_soundVolume");
	buffer->putString(to_string(data->p_soundVolume));
	buffer->putString("p_effectVolume");
	buffer->putString(to_string(data->p_effectVolume));
	buffer->writeToFile(filePath);
	return true;
}

bool GameSettingData::loadData(const string & path)
{
	auto filePath = path + "/GameSettingData.dat";
	auto data = GameSettingData::getSharedInstance();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto dataSize = buffer->getInt();
		for (int j = 0; j < dataSize; ++j) {
			string key = buffer->getString();
			string value = buffer->getString();
			if (data != nullptr) {
				if (key == "p_soundVolume") {
					data->p_soundVolume = atoi(value.c_str());
				} else if (key == "p_effectVolume") {
					data->p_effectVolume = atoi(value.c_str());
				}
			}
		}
	}
	return true;
}

bool GameSettingData::clearData()
{
	if (p_sharedData != nullptr) {
		delete p_sharedData;
		p_sharedData = nullptr;
	}
	return true;
}

void GameSettingData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "soundVolume") {
		this->setSoundVolume(atoi(value.c_str()));
	} else if (fieldName == "effectVolume") {
		this->setEffectVolume(atoi(value.c_str()));
	}
}

string GameSettingData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "soundVolume") {
		return to_string(this->getSoundVolume());
	} else if (fieldName == "effectVolume") {
		return to_string(this->getEffectVolume());
	}
	CCLOGWARN("Couldn't recognize %s in GameSettingData", fieldName.c_str());
	return "";
}

BaseData* GameSettingData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in GameSettingData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> GameSettingData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in GameSettingData", fieldName.c_str());
	return vector<BaseData *>();
}

