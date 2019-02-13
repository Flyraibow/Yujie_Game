/*
This file (EventData.cpp) is generated
*/
#include "EventData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, EventData*>* EventData::p_sharedDictionary = nullptr;

string EventData::getId() const
{
	return to_string(p_eventId);
}

string EventData::getEventId() const
{
	return p_eventId;
}

string EventData::getType() const
{
	return p_type;
}

map<string, string> EventData::getParametrsMap() const
{
	return p_parametrsMap;
}

string EventData::description() const
{
	string desc = "eventData = {\n";
	desc += "\teventId : " + to_string(p_eventId) + "\n";
	desc += "\ttype : " + to_string(p_type) + "\n";
	
	desc += "\tparametrs : " + to_string(p_parametrsMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, EventData*>* EventData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, EventData*>();
		static string resPath = "res/base/data/event.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				EventData* eventData = new EventData();
				eventData->p_eventId = buffer->getString();
				eventData->p_type = buffer->getString();
				auto parametrsCount = buffer->getLong();
				for (int j = 0; j < parametrsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getString();
					eventData->p_parametrsMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, EventData*>(eventData->p_eventId, eventData));
			}
		}
	}
	return p_sharedDictionary;
}

EventData* EventData::getEventDataById(const string& eventId)
{
	if (EventData::getSharedDictionary()->count(eventId)) {
		return EventData::getSharedDictionary()->at(eventId);
	}
	return nullptr;
}

string EventData::getFieldValue(const string & fieldName)
{
	if (fieldName == "eventId") {
		return to_string(this->getEventId());
	} else if (fieldName == "type") {
		return to_string(this->getType());
	} else if (fieldName == "parametrs") {
		return to_string(this->getParametrsMap());
	}
	CCLOGWARN("Couldn't recognize %s in EventData", fieldName.c_str());
	return "";
}

