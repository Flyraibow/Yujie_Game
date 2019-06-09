/*
This file (ScheduleTypeData.cpp) is generated
*/
#include "ScheduleTypeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ScheduleTypeData*>* ScheduleTypeData::p_sharedDictionary = nullptr;

string ScheduleTypeData::getId() const
{
	return to_string(p_scheduleTypeId);
}

string ScheduleTypeData::getScheduleTypeId() const
{
	return p_scheduleTypeId;
}

string ScheduleTypeData::getName() const
{
	string localId = "scheduleType_name_" + to_string(p_scheduleTypeId);
	return LocalizationHelper::getLocalization(localId);
}

string ScheduleTypeData::getProficienceWord() const
{
	string localId = "scheduleType_proficienceWord_" + to_string(p_scheduleTypeId);
	return LocalizationHelper::getLocalization(localId);
}

bool ScheduleTypeData::getSelectable() const
{
	return p_selectable;
}

string ScheduleTypeData::description() const
{
	string desc = "scheduleTypeData = {\n";
	desc += "\tscheduleTypeId : " + to_string(p_scheduleTypeId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tproficienceWord : " + getProficienceWord() + "\n";
	desc += "\tselectable : " + to_string(p_selectable) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ScheduleTypeData*>* ScheduleTypeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ScheduleTypeData*>();
		static string resPath = "res/base/data/scheduleType.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ScheduleTypeData* scheduleTypeData = new ScheduleTypeData();
				scheduleTypeData->p_scheduleTypeId = buffer->getString();
				scheduleTypeData->p_selectable = buffer->getChar();
				p_sharedDictionary->insert(pair<string, ScheduleTypeData*>(scheduleTypeData->p_scheduleTypeId, scheduleTypeData));
			}
		}
	}
	return p_sharedDictionary;
}

ScheduleTypeData* ScheduleTypeData::getScheduleTypeDataById(const string& scheduleTypeId)
{
	if (ScheduleTypeData::getSharedDictionary()->count(scheduleTypeId)) {
		return ScheduleTypeData::getSharedDictionary()->at(scheduleTypeId);
	}
	return nullptr;
}

string ScheduleTypeData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "scheduleTypeId") {
		return to_string(this->getScheduleTypeId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "proficienceWord") {
		return to_string(this->getProficienceWord());
	} else if (fieldName == "selectable") {
		return to_string(this->getSelectable());
	}
	CCLOGWARN("Couldn't recognize %s in ScheduleTypeData", fieldName.c_str());
	return "";
}

BaseData* ScheduleTypeData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ScheduleTypeData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ScheduleTypeData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ScheduleTypeData", fieldName.c_str());
	return vector<BaseData *>();
}

