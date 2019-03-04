/*
This file (SkillsData.cpp) is generated
*/
#include "SkillsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SkillsData*>* SkillsData::p_sharedDictionary = nullptr;

string SkillsData::getId() const
{
	return to_string(p_skillId);
}

string SkillsData::getSkillId() const
{
	return p_skillId;
}

string SkillsData::getName() const
{
	string localId = "skills_name_" + to_string(p_skillId);
	return LocalizationHelper::getLocalization(localId);
}

int SkillsData::getMaxValue() const
{
	return p_maxValue;
}

int SkillsData::getPassValue() const
{
	return p_passValue;
}

int SkillsData::getValue() const
{
	return p_value;
}

void SkillsData::setValue(int value)
{
	p_value = value;
}

set<SkillsData*> SkillsData::getRequiresDataSet() const
{
	set<SkillsData*> resultSet;
	for (auto objId : p_requiresIdSet) {
		resultSet.insert(SkillsData::getSkillsDataById(objId));
	}
	return resultSet;
}

set<string> SkillsData::getRequiresIdSet() const
{
	return p_requiresIdSet;
}

string SkillsData::description() const
{
	string desc = "skillsData = {\n";
	desc += "\tskillId : " + to_string(p_skillId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tmaxValue : " + to_string(p_maxValue) + "\n";
	desc += "\tpassValue : " + to_string(p_passValue) + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\trequires : " + to_string(p_requiresIdSet) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, SkillsData*>* SkillsData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SkillsData*>();
		static string resPath = "res/base/data/skills.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SkillsData* skillsData = new SkillsData();
				skillsData->p_skillId = buffer->getString();
				skillsData->p_maxValue = buffer->getInt();
				skillsData->p_passValue = buffer->getInt();
				skillsData->p_value = buffer->getInt();
				auto requiresCount = buffer->getLong();
				for (int j = 0; j < requiresCount; ++j) {
					skillsData->p_requiresIdSet.insert(buffer->getString());
				}
				p_sharedDictionary->insert(pair<string, SkillsData*>(skillsData->p_skillId, skillsData));
			}
		}
	}
	return p_sharedDictionary;
}

SkillsData* SkillsData::getSkillsDataById(const string& skillId)
{
	if (SkillsData::getSharedDictionary()->count(skillId)) {
		return SkillsData::getSharedDictionary()->at(skillId);
	}
	return nullptr;
}

bool SkillsData::saveData(const string & path)
{
	auto filePath = path + "/SkillsData.dat";
	auto dict = SkillsData::getSharedDictionary();
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

bool SkillsData::loadData(const string & path)
{
	auto filePath = path + "/SkillsData.dat";
	auto dict = SkillsData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			SkillsData *data = nullptr;
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

bool SkillsData::clearData()
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

void SkillsData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "value") {
		this->setValue(atoi(value.c_str()));
	}
}

string SkillsData::getFieldValue(const string & fieldName)
{
	if (fieldName == "skillId") {
		return to_string(this->getSkillId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "maxValue") {
		return to_string(this->getMaxValue());
	} else if (fieldName == "passValue") {
		return to_string(this->getPassValue());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	} else if (fieldName == "requires") {
		return to_string(this->getRequiresIdSet());
	}
	CCLOGWARN("Couldn't recognize %s in SkillsData", fieldName.c_str());
	return "";
}

BaseData* SkillsData::getDataByField(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in SkillsData", fieldName.c_str());
	return nullptr;
}

