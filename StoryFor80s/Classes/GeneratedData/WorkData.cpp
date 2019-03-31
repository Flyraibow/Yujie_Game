/*
This file (WorkData.cpp) is generated
*/
#include "WorkData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, WorkData*>* WorkData::p_sharedDictionary = nullptr;

string WorkData::getId() const
{
	return to_string(p_actionId);
}

string WorkData::getActionId() const
{
	return p_actionId;
}

string WorkData::getName() const
{
	string localId = "work_name_" + to_string(p_actionId);
	return LocalizationHelper::getLocalization(localId);
}

string WorkData::getCondition() const
{
	return p_condition;
}

int WorkData::getBaseSalary() const
{
	return p_baseSalary;
}

int WorkData::getRealSalary() const
{
	return p_realSalary;
}

void WorkData::setRealSalary(int realSalary)
{
	p_realSalary = realSalary;
}

int WorkData::getProficienc() const
{
	return p_proficienc;
}

void WorkData::setProficienc(int proficienc)
{
	p_proficienc = proficienc;
}

int WorkData::getMaxProficiency() const
{
	return p_maxProficiency;
}

map<string, int> WorkData::getAttributeChangeMap() const
{
	return p_attributeChangeMap;
}

map<string, int> WorkData::getPersonalityChangeMap() const
{
	return p_personalityChangeMap;
}

string WorkData::getDescription() const
{
	string localId = "work_description_" + to_string(p_actionId);
	return LocalizationHelper::getLocalization(localId);
}

string WorkData::description() const
{
	string desc = "workData = {\n";
	desc += "\tactionId : " + to_string(p_actionId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tbaseSalary : " + to_string(p_baseSalary) + "\n";
	desc += "\trealSalary : " + to_string(p_realSalary) + "\n";
	desc += "\tproficienc : " + to_string(p_proficienc) + "\n";
	desc += "\tmaxProficiency : " + to_string(p_maxProficiency) + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	
	desc += "\tpersonalityChange : " + to_string(p_personalityChangeMap)+ "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, WorkData*>* WorkData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, WorkData*>();
		static string resPath = "res/base/data/work.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				WorkData* workData = new WorkData();
				workData->p_actionId = buffer->getString();
				workData->p_condition = buffer->getString();
				workData->p_baseSalary = buffer->getInt();
				workData->p_realSalary = buffer->getInt();
				workData->p_proficienc = buffer->getInt();
				workData->p_maxProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					workData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				auto personalityChangeCount = buffer->getLong();
				for (int j = 0; j < personalityChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					workData->p_personalityChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, WorkData*>(workData->p_actionId, workData));
			}
		}
	}
	return p_sharedDictionary;
}

WorkData* WorkData::getWorkDataById(const string& actionId)
{
	if (WorkData::getSharedDictionary()->count(actionId)) {
		return WorkData::getSharedDictionary()->at(actionId);
	}
	return nullptr;
}

bool WorkData::saveData(const string & path)
{
	auto filePath = path + "/WorkData.dat";
	auto dict = WorkData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(2);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_realSalary");
		buffer->putString(to_string(data->p_realSalary));
		buffer->putString("p_proficienc");
		buffer->putString(to_string(data->p_proficienc));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool WorkData::loadData(const string & path)
{
	auto filePath = path + "/WorkData.dat";
	auto dict = WorkData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			WorkData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_realSalary") {
						data->p_realSalary = atoi(value.c_str());
					} else if (key == "p_proficienc") {
						data->p_proficienc = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool WorkData::clearData()
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

void WorkData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "realSalary") {
		this->setRealSalary(atoi(value.c_str()));
	} else if (fieldName == "proficienc") {
		this->setProficienc(atoi(value.c_str()));
	}
}

string WorkData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "actionId") {
		return to_string(this->getActionId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "baseSalary") {
		return to_string(this->getBaseSalary());
	} else if (fieldName == "realSalary") {
		return to_string(this->getRealSalary());
	} else if (fieldName == "proficienc") {
		return to_string(this->getProficienc());
	} else if (fieldName == "maxProficiency") {
		return to_string(this->getMaxProficiency());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	} else if (fieldName == "personalityChange") {
		return to_string(this->getPersonalityChangeMap());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	}
	CCLOGWARN("Couldn't recognize %s in WorkData", fieldName.c_str());
	return "";
}

BaseData* WorkData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in WorkData", fieldName.c_str());
	return nullptr;
}

