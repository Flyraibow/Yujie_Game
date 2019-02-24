/*
This file (StoryData.cpp) is generated
*/
#include "StoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, StoryData*>* StoryData::p_sharedDictionary = nullptr;

string StoryData::getId() const
{
	return to_string(p_storyId);
}

string StoryData::getStoryId() const
{
	return p_storyId;
}

string StoryData::getStoryEvent() const
{
	return p_storyEvent;
}

bool StoryData::getOnce() const
{
	return p_once;
}

int StoryData::getCount() const
{
	return p_count;
}

void StoryData::setCount(int count)
{
	p_count = count;
}

ConditionData* StoryData::getConditionData() const
{
	return ConditionData::getConditionDataById(p_conditionId);
}

string StoryData::getConditionId() const
{
	return p_conditionId;
}

string StoryData::description() const
{
	string desc = "storyData = {\n";
	desc += "\tstoryId : " + to_string(p_storyId) + "\n";
	desc += "\tstoryEvent : " + to_string(p_storyEvent) + "\n";
	desc += "\tonce : " + to_string(p_once) + "\n";
	desc += "\tcount : " + to_string(p_count) + "\n";
	desc += "\tcondition : " + to_string(p_conditionId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, StoryData*>* StoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, StoryData*>();
		static string resPath = "res/base/data/story.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				StoryData* storyData = new StoryData();
				storyData->p_storyId = buffer->getString();
				storyData->p_storyEvent = buffer->getString();
				storyData->p_once = buffer->getChar();
				storyData->p_count = buffer->getInt();
				storyData->p_conditionId = buffer->getString();
				p_sharedDictionary->insert(pair<string, StoryData*>(storyData->p_storyId, storyData));
			}
		}
	}
	return p_sharedDictionary;
}

StoryData* StoryData::getStoryDataById(const string& storyId)
{
	if (StoryData::getSharedDictionary()->count(storyId)) {
		return StoryData::getSharedDictionary()->at(storyId);
	}
	return nullptr;
}

bool StoryData::saveData(const string & path)
{
	auto filePath = path + "/StoryData.dat";
	auto dict = StoryData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_count");
		buffer->putString(to_string(data->p_count));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool StoryData::loadData(const string & path)
{
	auto filePath = path + "/StoryData.dat";
	auto dict = StoryData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			StoryData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_count") {
						data->p_count = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool StoryData::clearData()
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

void StoryData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "count") {
		this->setCount(atoi(value.c_str()));
	}
}

string StoryData::getFieldValue(const string & fieldName)
{
	if (fieldName == "storyId") {
		return to_string(this->getStoryId());
	} else if (fieldName == "storyEvent") {
		return to_string(this->getStoryEvent());
	} else if (fieldName == "once") {
		return to_string(this->getOnce());
	} else if (fieldName == "count") {
		return to_string(this->getCount());
	} else if (fieldName == "condition") {
		return to_string(this->getConditionId());
	}
	CCLOGWARN("Couldn't recognize %s in StoryData", fieldName.c_str());
	return "";
}

