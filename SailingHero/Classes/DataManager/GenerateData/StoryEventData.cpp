/*
This file (StoryEventData.cpp) is generated
*/
#include "StoryEventData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, StoryEventData*>* StoryEventData::p_sharedDictionary = nullptr;

string StoryEventData::getId() const
{
	return to_string(p_storyEventId);
}

string StoryEventData::getStoryEventId() const
{
	return p_storyEventId;
}

string StoryEventData::getType() const
{
	return p_type;
}

double StoryEventData::getDuration() const
{
	return p_duration;
}

string StoryEventData::getName() const
{
	return p_name;
}

string StoryEventData::getPath() const
{
	return p_path;
}

map<string, string> StoryEventData::getParametrsMap() const
{
	return p_parametrsMap;
}

StoryEventData* StoryEventData::getNextStoryData() const
{
	return StoryEventData::getStoryEventDataById(p_nextStoryId);
}

string StoryEventData::getNextStoryId() const
{
	return p_nextStoryId;
}

string StoryEventData::description() const
{
	string desc = "storyEventData = {\n";
	desc += "\tstoryEventId : " + to_string(p_storyEventId) + "\n";
	desc += "\ttype : " + to_string(p_type) + "\n";
	desc += "\tduration : " + to_string(p_duration) + "\n";
	desc += "\tname : " + to_string(p_name) + "\n";
	desc += "\tpath : " + to_string(p_path) + "\n";
	
	desc += "\tparametrs : " + to_string(p_parametrsMap)+ "\n";
	desc += "\tnextStory : " + to_string(p_nextStoryId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, StoryEventData*>* StoryEventData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, StoryEventData*>();
		static string resPath = "res/base/data/storyEvent.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				StoryEventData* storyEventData = new StoryEventData();
				storyEventData->p_storyEventId = buffer->getString();
				storyEventData->p_type = buffer->getString();
				storyEventData->p_duration = buffer->getDouble();
				storyEventData->p_name = buffer->getString();
				storyEventData->p_path = buffer->getString();
				auto parametrsCount = buffer->getLong();
				for (int j = 0; j < parametrsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getString();
					storyEventData->p_parametrsMap.insert(make_pair(key, val));
				}
				storyEventData->p_nextStoryId = buffer->getString();
				p_sharedDictionary->insert(pair<string, StoryEventData*>(storyEventData->p_storyEventId, storyEventData));
			}
		}
	}
	return p_sharedDictionary;
}

StoryEventData* StoryEventData::getStoryEventDataById(const string& storyEventId)
{
	if (StoryEventData::getSharedDictionary()->count(storyEventId)) {
		return StoryEventData::getSharedDictionary()->at(storyEventId);
	}
	return nullptr;
}

string StoryEventData::getFieldValue(const string & fieldName)
{
	if (fieldName == "storyEventId") {
		return to_string(this->getStoryEventId());
	} else if (fieldName == "type") {
		return to_string(this->getType());
	} else if (fieldName == "duration") {
		return to_string(this->getDuration());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "path") {
		return to_string(this->getPath());
	} else if (fieldName == "parametrs") {
		return to_string(this->getParametrsMap());
	} else if (fieldName == "nextStory") {
		return to_string(this->getNextStoryId());
	}
	CCLOGWARN("Couldn't recognize %s in StoryEventData", fieldName.c_str());
	return "";
}

