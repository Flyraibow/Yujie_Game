/*
This file (HobbyData.cpp) is generated
*/
#include "HobbyData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, HobbyData*>* HobbyData::p_sharedDictionary = nullptr;

string HobbyData::getId() const
{
	return to_string(p_hobbyId);
}

string HobbyData::getHobbyId() const
{
	return p_hobbyId;
}

string HobbyData::getName() const
{
	string localId = "hobby_name_" + to_string(p_hobbyId);
	return LocalizationHelper::getLocalization(localId);
}

int HobbyData::getExpense() const
{
	return p_expense;
}

int HobbyData::getProficiency() const
{
	return p_proficiency;
}

void HobbyData::setProficiency(int proficiency)
{
	p_proficiency = proficiency;
}

string HobbyData::description() const
{
	string desc = "hobbyData = {\n";
	desc += "\thobbyId : " + to_string(p_hobbyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\texpense : " + to_string(p_expense) + "\n";
	desc += "\tproficiency : " + to_string(p_proficiency) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, HobbyData*>* HobbyData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, HobbyData*>();
		static string resPath = "res/base/data/hobby.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				HobbyData* hobbyData = new HobbyData();
				hobbyData->p_hobbyId = buffer->getString();
				hobbyData->p_expense = buffer->getInt();
				hobbyData->p_proficiency = buffer->getInt();
				p_sharedDictionary->insert(pair<string, HobbyData*>(hobbyData->p_hobbyId, hobbyData));
			}
		}
	}
	return p_sharedDictionary;
}

HobbyData* HobbyData::getHobbyDataById(const string& hobbyId)
{
	if (HobbyData::getSharedDictionary()->count(hobbyId)) {
		return HobbyData::getSharedDictionary()->at(hobbyId);
	}
	return nullptr;
}

bool HobbyData::saveData(const string & path)
{
	auto filePath = path + "/HobbyData.dat";
	auto dict = HobbyData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_proficiency");
		buffer->putString(to_string(data->p_proficiency));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool HobbyData::loadData(const string & path)
{
	auto filePath = path + "/HobbyData.dat";
	auto dict = HobbyData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			HobbyData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_proficiency") {
						data->p_proficiency = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool HobbyData::clearData()
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

void HobbyData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "proficiency") {
		this->setProficiency(atoi(value.c_str()));
	}
}

string HobbyData::getFieldValue(const string & fieldName)
{
	if (fieldName == "hobbyId") {
		return to_string(this->getHobbyId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "expense") {
		return to_string(this->getExpense());
	} else if (fieldName == "proficiency") {
		return to_string(this->getProficiency());
	}
	CCLOGWARN("Couldn't recognize %s in HobbyData", fieldName.c_str());
	return "";
}
