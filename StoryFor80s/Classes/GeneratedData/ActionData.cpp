/*
This file (ActionData.cpp) is generated
*/
#include "ActionData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<string, ActionData*>* ActionData::p_sharedDictionary = nullptr;

string ActionData::getId() const
{
	return to_string(p_actionId);
}

string ActionData::getActionId() const
{
	return p_actionId;
}

string ActionData::getName() const
{
	string localId = "action_name_" + to_string(p_actionId);
	return LocalizationHelper::getLocalization(localId);
}

EventData* ActionData::getEventData() const
{
	return EventData::getEventDataById(p_eventId);
}

string ActionData::getEventId() const
{
	return p_eventId;
}

string ActionData::description() const
{
	string desc = "actionData = {\n";
	desc += "\tactionId : " + to_string(p_actionId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tevent : " + to_string(p_eventId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ActionData*>* ActionData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ActionData*>();
		static string resPath = "res/base/data/action.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ActionData* actionData = new ActionData();
				actionData->p_actionId = buffer->getString();
				actionData->p_eventId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ActionData*>(actionData->p_actionId, actionData));
			}
		}
	}
	return p_sharedDictionary;
}

ActionData* ActionData::getActionDataById(const string& actionId)
{
	if (ActionData::getSharedDictionary()->count(actionId)) {
		return ActionData::getSharedDictionary()->at(actionId);
	}
	return nullptr;
}

string ActionData::getFieldValue(const string & fieldName)
{
	if (fieldName == "actionId") {
		return to_string(this->getActionId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "event") {
		return to_string(this->getEventId());
	}
	CCLOGWARN("Couldn't recognize %s in ActionData", fieldName.c_str());
	return "";
}
