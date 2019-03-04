/*
This file (FatherJobData.cpp) is generated
*/
#include "FatherJobData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, FatherJobData*>* FatherJobData::p_sharedDictionary = nullptr;

string FatherJobData::getId() const
{
	return to_string(p_fatherJobId);
}

string FatherJobData::getFatherJobId() const
{
	return p_fatherJobId;
}

string FatherJobData::getName() const
{
	string localId = "fatherJob_name_" + to_string(p_fatherJobId);
	return LocalizationHelper::getLocalization(localId);
}

int FatherJobData::getSalary() const
{
	return p_salary;
}

void FatherJobData::setSalary(int salary)
{
	p_salary = salary;
}

int FatherJobData::getKnowledge() const
{
	return p_knowledge;
}

void FatherJobData::setKnowledge(int knowledge)
{
	p_knowledge = knowledge;
}

string FatherJobData::getDescription() const
{
	string localId = "fatherJob_description_" + to_string(p_fatherJobId);
	return LocalizationHelper::getLocalization(localId);
}

string FatherJobData::description() const
{
	string desc = "fatherJobData = {\n";
	desc += "\tfatherJobId : " + to_string(p_fatherJobId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tsalary : " + to_string(p_salary) + "\n";
	desc += "\tknowledge : " + to_string(p_knowledge) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, FatherJobData*>* FatherJobData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, FatherJobData*>();
		static string resPath = "res/base/data/fatherJob.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				FatherJobData* fatherJobData = new FatherJobData();
				fatherJobData->p_fatherJobId = buffer->getString();
				fatherJobData->p_salary = buffer->getInt();
				fatherJobData->p_knowledge = buffer->getInt();
				p_sharedDictionary->insert(pair<string, FatherJobData*>(fatherJobData->p_fatherJobId, fatherJobData));
			}
		}
	}
	return p_sharedDictionary;
}

FatherJobData* FatherJobData::getFatherJobDataById(const string& fatherJobId)
{
	if (FatherJobData::getSharedDictionary()->count(fatherJobId)) {
		return FatherJobData::getSharedDictionary()->at(fatherJobId);
	}
	return nullptr;
}

bool FatherJobData::saveData(const string & path)
{
	auto filePath = path + "/FatherJobData.dat";
	auto dict = FatherJobData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(2);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_salary");
		buffer->putString(to_string(data->p_salary));
		buffer->putString("p_knowledge");
		buffer->putString(to_string(data->p_knowledge));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool FatherJobData::loadData(const string & path)
{
	auto filePath = path + "/FatherJobData.dat";
	auto dict = FatherJobData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			FatherJobData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_salary") {
						data->p_salary = atoi(value.c_str());
					} else if (key == "p_knowledge") {
						data->p_knowledge = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool FatherJobData::clearData()
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

void FatherJobData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "salary") {
		this->setSalary(atoi(value.c_str()));
	} else if (fieldName == "knowledge") {
		this->setKnowledge(atoi(value.c_str()));
	}
}

string FatherJobData::getFieldValue(const string & fieldName)
{
	if (fieldName == "fatherJobId") {
		return to_string(this->getFatherJobId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "salary") {
		return to_string(this->getSalary());
	} else if (fieldName == "knowledge") {
		return to_string(this->getKnowledge());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	}
	CCLOGWARN("Couldn't recognize %s in FatherJobData", fieldName.c_str());
	return "";
}

BaseData* FatherJobData::getDataByField(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in FatherJobData", fieldName.c_str());
	return nullptr;
}

