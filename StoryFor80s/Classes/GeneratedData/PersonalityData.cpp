/*
This file (PersonalityData.cpp) is generated
*/
#include "PersonalityData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, PersonalityData*>* PersonalityData::p_sharedDictionary = nullptr;

string PersonalityData::getId() const
{
	return to_string(p_attributeId);
}

string PersonalityData::getAttributeId() const
{
	return p_attributeId;
}

string PersonalityData::getName() const
{
	string localId = "personality_name_" + to_string(p_attributeId);
	return LocalizationHelper::getLocalization(localId);
}

int PersonalityData::getValue() const
{
	return p_value;
}

void PersonalityData::setValue(int value)
{
	p_value = value;
}

string PersonalityData::description() const
{
	string desc = "personalityData = {\n";
	desc += "\tattributeId : " + to_string(p_attributeId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, PersonalityData*>* PersonalityData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, PersonalityData*>();
		static string resPath = "res/base/data/personality.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				PersonalityData* personalityData = new PersonalityData();
				personalityData->p_attributeId = buffer->getString();
				personalityData->p_value = buffer->getInt();
				p_sharedDictionary->insert(pair<string, PersonalityData*>(personalityData->p_attributeId, personalityData));
			}
		}
	}
	return p_sharedDictionary;
}

PersonalityData* PersonalityData::getPersonalityDataById(const string& attributeId)
{
	if (PersonalityData::getSharedDictionary()->count(attributeId)) {
		return PersonalityData::getSharedDictionary()->at(attributeId);
	}
	return nullptr;
}

bool PersonalityData::saveData(const string & path)
{
	auto filePath = path + "/PersonalityData.dat";
	auto dict = PersonalityData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_value");
		buffer->putString(to_string(data->p_value));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool PersonalityData::loadData(const string & path)
{
	auto filePath = path + "/PersonalityData.dat";
	auto dict = PersonalityData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			PersonalityData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_value") {
						data->p_value = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool PersonalityData::clearData()
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

void PersonalityData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "value") {
		this->setValue(atoi(value.c_str()));
	}
}

string PersonalityData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "attributeId") {
		return to_string(this->getAttributeId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	}
	CCLOGWARN("Couldn't recognize %s in PersonalityData", fieldName.c_str());
	return "";
}

BaseData* PersonalityData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in PersonalityData", fieldName.c_str());
	return nullptr;
}

