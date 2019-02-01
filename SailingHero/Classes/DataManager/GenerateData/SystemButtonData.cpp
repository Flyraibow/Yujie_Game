/*
This file (SystemButtonData.cpp) is generated
*/
#include "SystemButtonData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<int, SystemButtonData*>* SystemButtonData::p_sharedDictionary = nullptr;

string SystemButtonData::getId() const
{
	return to_string(p_buttonId);
}

int SystemButtonData::getButtonId() const
{
	return p_buttonId;
}

string SystemButtonData::getButtonName() const
{
	string localId = "systemButton_buttonName_" + to_string(p_buttonId);
	return LocalizationHelper::getLocalization(localId);
}

EventData* SystemButtonData::getEventData() const
{
	return EventData::getEventDataById(p_eventId);
}

string SystemButtonData::getEventId() const
{
	return p_eventId;
}

string SystemButtonData::description() const
{
	string desc = "systemButtonData = {\n";
	desc += "\tbuttonId : " + to_string(p_buttonId) + "\n";
	desc += "\tbuttonName : " + getButtonName() + "\n";
	desc += "\tevent : " + to_string(p_eventId) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, SystemButtonData*>* SystemButtonData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, SystemButtonData*>();
		static string resPath = "res/base/data/systemButton.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SystemButtonData* systemButtonData = new SystemButtonData();
				systemButtonData->p_buttonId = buffer->getInt();
				systemButtonData->p_eventId = buffer->getString();
				p_sharedDictionary->insert(pair<int, SystemButtonData*>(systemButtonData->p_buttonId, systemButtonData));
			}
		}
	}
	return p_sharedDictionary;
}

SystemButtonData* SystemButtonData::getSystemButtonDataById(int buttonId)
{
	if (SystemButtonData::getSharedDictionary()->count(buttonId)) {
		return SystemButtonData::getSharedDictionary()->at(buttonId);
	}
	return nullptr;
}

SystemButtonData* SystemButtonData::getSystemButtonDataById(const string& buttonId)
{
	if (buttonId.length() == 0) return nullptr;
	return SystemButtonData::getSystemButtonDataById(atoi(buttonId.c_str()));
}

string SystemButtonData::getFieldValue(const string & fieldName)
{
	if (fieldName == "buttonId") {
		return to_string(this->getButtonId());
	} else if (fieldName == "buttonName") {
		return to_string(this->getButtonName());
	} else if (fieldName == "event") {
		return to_string(this->getEventId());
	}
	CCLOGWARN("Couldn't recognize %s in SystemButtonData", fieldName.c_str());
	return "";
}

