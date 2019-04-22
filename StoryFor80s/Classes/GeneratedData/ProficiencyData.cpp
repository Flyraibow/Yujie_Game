/*
This file (ProficiencyData.cpp) is generated
*/
#include "ProficiencyData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ProficiencyData*>* ProficiencyData::p_sharedDictionary = nullptr;

string ProficiencyData::getId() const
{
	return to_string(p_proficiencyId);
}

string ProficiencyData::getProficiencyId() const
{
	return p_proficiencyId;
}

string ProficiencyData::getName() const
{
	string localId = "proficiency_name_" + to_string(p_proficiencyId);
	return LocalizationHelper::getLocalization(localId);
}

int ProficiencyData::getValue() const
{
	return p_value;
}

void ProficiencyData::setValue(int value)
{
	p_value = value;
}

int ProficiencyData::getMaxValue() const
{
	return p_maxValue;
}

string ProficiencyData::description() const
{
	string desc = "proficiencyData = {\n";
	desc += "\tproficiencyId : " + to_string(p_proficiencyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\tmaxValue : " + to_string(p_maxValue) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ProficiencyData*>* ProficiencyData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ProficiencyData*>();
		static string resPath = "res/base/data/proficiency.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ProficiencyData* proficiencyData = new ProficiencyData();
				proficiencyData->p_proficiencyId = buffer->getString();
				proficiencyData->p_value = buffer->getInt();
				proficiencyData->p_maxValue = buffer->getInt();
				p_sharedDictionary->insert(pair<string, ProficiencyData*>(proficiencyData->p_proficiencyId, proficiencyData));
			}
		}
	}
	return p_sharedDictionary;
}

ProficiencyData* ProficiencyData::getProficiencyDataById(const string& proficiencyId)
{
	if (ProficiencyData::getSharedDictionary()->count(proficiencyId)) {
		return ProficiencyData::getSharedDictionary()->at(proficiencyId);
	}
	return nullptr;
}

bool ProficiencyData::saveData(const string & path)
{
	auto filePath = path + "/ProficiencyData.dat";
	auto dict = ProficiencyData::getSharedDictionary();
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

bool ProficiencyData::loadData(const string & path)
{
	auto filePath = path + "/ProficiencyData.dat";
	auto dict = ProficiencyData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			ProficiencyData *data = nullptr;
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

bool ProficiencyData::clearData()
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

void ProficiencyData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "value") {
		this->setValue(atoi(value.c_str()));
	}
}

string ProficiencyData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "proficiencyId") {
		return to_string(this->getProficiencyId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	} else if (fieldName == "maxValue") {
		return to_string(this->getMaxValue());
	}
	CCLOGWARN("Couldn't recognize %s in ProficiencyData", fieldName.c_str());
	return "";
}

BaseData* ProficiencyData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ProficiencyData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ProficiencyData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ProficiencyData", fieldName.c_str());
	return vector<BaseData *>();
}

