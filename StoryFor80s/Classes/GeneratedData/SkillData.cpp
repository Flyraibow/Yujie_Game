/*
This file (SkillData.cpp) is generated
*/
#include "SkillData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, SkillData*>* SkillData::p_sharedDictionary = nullptr;

string SkillData::getId() const
{
	return to_string(p_skillId);
}

string SkillData::getSkillId() const
{
	return p_skillId;
}

bool SkillData::getHaveIt() const
{
	return p_haveIt;
}

void SkillData::setHaveIt(bool haveIt)
{
	p_haveIt = haveIt;
}

string SkillData::description() const
{
	string desc = "skillData = {\n";
	desc += "\tskillId : " + to_string(p_skillId) + "\n";
	desc += "\thaveIt : " + to_string(p_haveIt) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, SkillData*>* SkillData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SkillData*>();
		static string resPath = "res/base/data/skill.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SkillData* skillData = new SkillData();
				skillData->p_skillId = buffer->getString();
				skillData->p_haveIt = buffer->getChar();
				p_sharedDictionary->insert(pair<string, SkillData*>(skillData->p_skillId, skillData));
			}
		}
	}
	return p_sharedDictionary;
}

SkillData* SkillData::getSkillDataById(const string& skillId)
{
	if (SkillData::getSharedDictionary()->count(skillId)) {
		return SkillData::getSharedDictionary()->at(skillId);
	}
	return nullptr;
}

bool SkillData::saveData(const string & path)
{
	auto filePath = path + "/SkillData.dat";
	auto dict = SkillData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_haveIt");
		buffer->putString(to_string(data->p_haveIt));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool SkillData::loadData(const string & path)
{
	auto filePath = path + "/SkillData.dat";
	auto dict = SkillData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			SkillData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_haveIt") {
						data->p_haveIt = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool SkillData::clearData()
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

void SkillData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "haveIt") {
		this->setHaveIt((atoi(value.c_str()) != 0));
	}
}

string SkillData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "skillId") {
		return to_string(this->getSkillId());
	} else if (fieldName == "haveIt") {
		return to_string(this->getHaveIt());
	}
	CCLOGWARN("Couldn't recognize %s in SkillData", fieldName.c_str());
	return "";
}

BaseData* SkillData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in SkillData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> SkillData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in SkillData", fieldName.c_str());
	return vector<BaseData *>();
}

