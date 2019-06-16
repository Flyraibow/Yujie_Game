/*
This file (ParentChatData.cpp) is generated
*/
#include "ParentChatData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, ParentChatData*>* ParentChatData::p_sharedDictionary = nullptr;

string ParentChatData::getId() const
{
	return to_string(p_chatId);
}

string ParentChatData::getChatId() const
{
	return p_chatId;
}

int ParentChatData::getPriority() const
{
	return p_priority;
}

int ParentChatData::getStartYear() const
{
	return p_startYear;
}

int ParentChatData::getStartMonth() const
{
	return p_startMonth;
}

int ParentChatData::getEndYear() const
{
	return p_endYear;
}

int ParentChatData::getEndMonth() const
{
	return p_endMonth;
}

string ParentChatData::getCondition() const
{
	return p_condition;
}

bool ParentChatData::getRepeat() const
{
	return p_repeat;
}

bool ParentChatData::getExperienced() const
{
	return p_experienced;
}

void ParentChatData::setExperienced(bool experienced)
{
	p_experienced = experienced;
}

string ParentChatData::getStory() const
{
	return p_story;
}

string ParentChatData::description() const
{
	string desc = "parentChatData = {\n";
	desc += "\tchatId : " + to_string(p_chatId) + "\n";
	desc += "\tpriority : " + to_string(p_priority) + "\n";
	desc += "\tstartYear : " + to_string(p_startYear) + "\n";
	desc += "\tstartMonth : " + to_string(p_startMonth) + "\n";
	desc += "\tendYear : " + to_string(p_endYear) + "\n";
	desc += "\tendMonth : " + to_string(p_endMonth) + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\trepeat : " + to_string(p_repeat) + "\n";
	desc += "\texperienced : " + to_string(p_experienced) + "\n";
	desc += "\tstory : " + to_string(p_story) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ParentChatData*>* ParentChatData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ParentChatData*>();
		static string resPath = "res/base/data/parentChat.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ParentChatData* parentChatData = new ParentChatData();
				parentChatData->p_chatId = buffer->getString();
				parentChatData->p_priority = buffer->getInt();
				parentChatData->p_startYear = buffer->getInt();
				parentChatData->p_startMonth = buffer->getInt();
				parentChatData->p_endYear = buffer->getInt();
				parentChatData->p_endMonth = buffer->getInt();
				parentChatData->p_condition = buffer->getString();
				parentChatData->p_repeat = buffer->getChar();
				parentChatData->p_experienced = buffer->getChar();
				parentChatData->p_story = buffer->getString();
				p_sharedDictionary->insert(pair<string, ParentChatData*>(parentChatData->p_chatId, parentChatData));
			}
		}
	}
	return p_sharedDictionary;
}

ParentChatData* ParentChatData::getParentChatDataById(const string& chatId)
{
	if (ParentChatData::getSharedDictionary()->count(chatId)) {
		return ParentChatData::getSharedDictionary()->at(chatId);
	}
	return nullptr;
}

bool ParentChatData::saveData(const string & path)
{
	auto filePath = path + "/ParentChatData.dat";
	auto dict = ParentChatData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_experienced");
		buffer->putString(to_string(data->p_experienced));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool ParentChatData::loadData(const string & path)
{
	auto filePath = path + "/ParentChatData.dat";
	auto dict = ParentChatData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			ParentChatData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_experienced") {
						data->p_experienced = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool ParentChatData::clearData()
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

void ParentChatData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "experienced") {
		this->setExperienced((atoi(value.c_str()) != 0));
	}
}

string ParentChatData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "chatId") {
		return to_string(this->getChatId());
	} else if (fieldName == "priority") {
		return to_string(this->getPriority());
	} else if (fieldName == "startYear") {
		return to_string(this->getStartYear());
	} else if (fieldName == "startMonth") {
		return to_string(this->getStartMonth());
	} else if (fieldName == "endYear") {
		return to_string(this->getEndYear());
	} else if (fieldName == "endMonth") {
		return to_string(this->getEndMonth());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "repeat") {
		return to_string(this->getRepeat());
	} else if (fieldName == "experienced") {
		return to_string(this->getExperienced());
	} else if (fieldName == "story") {
		return to_string(this->getStory());
	}
	CCLOGWARN("Couldn't recognize %s in ParentChatData", fieldName.c_str());
	return "";
}

BaseData* ParentChatData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ParentChatData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ParentChatData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ParentChatData", fieldName.c_str());
	return vector<BaseData *>();
}

