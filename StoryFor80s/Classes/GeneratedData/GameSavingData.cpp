/*
This file (GameSavingData.cpp) is generated
*/
#include "GameSavingData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<int, GameSavingData*>* GameSavingData::p_sharedDictionary = nullptr;

string GameSavingData::getId() const
{
	return to_string(p_savingId);
}

int GameSavingData::getSavingId() const
{
	return p_savingId;
}

void GameSavingData::setSaveDescription(string saveDescription)
{
	p_saveDescription = saveDescription;
}

string GameSavingData::getSaveDescription() const
{
	if (p_saveDescription.length() > 0) {
		return p_saveDescription;
	}
	string localId = "gameSaving_saveDescription_" + to_string(p_savingId);
	return LocalizationHelper::getLocalization(localId);
}

bool GameSavingData::getSaved() const
{
	return p_saved;
}

void GameSavingData::setSaved(bool saved)
{
	p_saved = saved;
}

string GameSavingData::description() const
{
	string desc = "gameSavingData = {\n";
	desc += "\tsavingId : " + to_string(p_savingId) + "\n";
	desc += "\tsaveDescription : " + getSaveDescription() + "\n";
	desc += "\tsaved : " + to_string(p_saved) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, GameSavingData*>* GameSavingData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, GameSavingData*>();
		static string resPath = "res/base/data/gameSaving.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GameSavingData* gameSavingData = new GameSavingData();
				gameSavingData->p_savingId = buffer->getInt();
				gameSavingData->p_saved = buffer->getChar();
				p_sharedDictionary->insert(pair<int, GameSavingData*>(gameSavingData->p_savingId, gameSavingData));
			}
		}
	}
	return p_sharedDictionary;
}

GameSavingData* GameSavingData::getGameSavingDataById(int savingId)
{
	if (GameSavingData::getSharedDictionary()->count(savingId)) {
		return GameSavingData::getSharedDictionary()->at(savingId);
	}
	return nullptr;
}

GameSavingData* GameSavingData::getGameSavingDataById(const string& savingId)
{
	if (savingId.length() == 0) return nullptr;
	return GameSavingData::getGameSavingDataById(atoi(savingId.c_str()));
}

bool GameSavingData::saveData(const string & path)
{
	auto filePath = path + "/GameSavingData.dat";
	auto dict = GameSavingData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(2);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_saveDescription");
		buffer->putString(to_string(data->p_saveDescription));
		buffer->putString("p_saved");
		buffer->putString(to_string(data->p_saved));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool GameSavingData::loadData(const string & path)
{
	auto filePath = path + "/GameSavingData.dat";
	auto dict = GameSavingData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			GameSavingData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_saveDescription") {
						data->p_saveDescription = value;
					} else if (key == "p_saved") {
						data->p_saved = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool GameSavingData::clearData()
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

void GameSavingData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "saveDescription") {
		this->setSaveDescription(value);
	} else if (fieldName == "saved") {
		this->setSaved((atoi(value.c_str()) != 0));
	}
}

string GameSavingData::getFieldValue(const string & fieldName)
{
	if (fieldName == "savingId") {
		return to_string(this->getSavingId());
	} else if (fieldName == "saveDescription") {
		return to_string(this->getSaveDescription());
	} else if (fieldName == "saved") {
		return to_string(this->getSaved());
	}
	CCLOGWARN("Couldn't recognize %s in GameSavingData", fieldName.c_str());
	return "";
}

