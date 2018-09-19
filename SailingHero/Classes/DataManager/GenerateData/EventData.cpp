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

string EventData::getEventType() const
{
	return p_eventType;
}

vector<string> EventData::getParameters() const
{
	return p_parameters;
}

string EventData::description() const
{
	string desc = "eventData = {\n";
	desc += "\teventId : " + to_string(p_eventId) + "\n";
	desc += "\teventType : " + to_string(p_eventType) + "\n";
	desc += "\tparameters : " + to_string(p_parameters) + "\n";
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
				eventData->p_eventType = buffer->getString();
				auto parametersCount = buffer->getLong();
				for (int j = 0; j < parametersCount; ++j) {
					eventData->p_parameters.push_back(buffer->getString());
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
	} else if (fieldName == "eventType") {
		return to_string(this->getEventType());
	} else if (fieldName == "parameters") {
		return to_string(this->getParameters());
	}
	CCLOGWARN("Couldn't recognize %s in EventData", fieldName.c_str());
	return "";
}

