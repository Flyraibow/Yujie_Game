/*
This file (ButtonData.cpp) is generated
*/
#include "ButtonData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<string, ButtonData*>* ButtonData::p_sharedDictionary = nullptr;

string ButtonData::getId() const
{
	return to_string(p_buttonId);
}

string ButtonData::getButtonId() const
{
	return p_buttonId;
}

string ButtonData::getLabel() const
{
	string localId = "button_label_" + to_string(p_buttonId);
	return LocalizationHelper::getLocalization(localId);
}

ConditionData* ButtonData::getConditionData() const
{
	return ConditionData::getConditionDataById(p_conditionId);
}

string ButtonData::getConditionId() const
{
	return p_conditionId;
}

EventData* ButtonData::getTriggerEventData() const
{
	return EventData::getEventDataById(p_triggerEventId);
}

string ButtonData::getTriggerEventId() const
{
	return p_triggerEventId;
}

StoryEventData* ButtonData::getTriggerStoryData() const
{
	return StoryEventData::getStoryEventDataById(p_triggerStoryId);
}

string ButtonData::getTriggerStoryId() const
{
	return p_triggerStoryId;
}

string ButtonData::description() const
{
	string desc = "buttonData = {\n";
	desc += "\tbuttonId : " + to_string(p_buttonId) + "\n";
	desc += "\tlabel : " + getLabel() + "\n";
	desc += "\tcondition : " + to_string(p_conditionId) + "\n";
	desc += "\ttriggerEvent : " + to_string(p_triggerEventId) + "\n";
	desc += "\ttriggerStory : " + to_string(p_triggerStoryId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ButtonData*>* ButtonData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ButtonData*>();
		static string resPath = "res/base/data/button.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ButtonData* buttonData = new ButtonData();
				buttonData->p_buttonId = buffer->getString();
				buttonData->p_conditionId = buffer->getString();
				buttonData->p_triggerEventId = buffer->getString();
				buttonData->p_triggerStoryId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ButtonData*>(buttonData->p_buttonId, buttonData));
			}
		}
	}
	return p_sharedDictionary;
}

ButtonData* ButtonData::getButtonDataById(const string& buttonId)
{
	if (ButtonData::getSharedDictionary()->count(buttonId)) {
		return ButtonData::getSharedDictionary()->at(buttonId);
	}
	return nullptr;
}

string ButtonData::getFieldValue(const string & fieldName)
{
	if (fieldName == "buttonId") {
		return to_string(this->getButtonId());
	} else if (fieldName == "label") {
		return to_string(this->getLabel());
	} else if (fieldName == "condition") {
		return to_string(this->getConditionId());
	} else if (fieldName == "triggerEvent") {
		return to_string(this->getTriggerEventId());
	} else if (fieldName == "triggerStory") {
		return to_string(this->getTriggerStoryId());
	}
	CCLOGWARN("Couldn't recognize %s in ButtonData", fieldName.c_str());
	return "";
}

