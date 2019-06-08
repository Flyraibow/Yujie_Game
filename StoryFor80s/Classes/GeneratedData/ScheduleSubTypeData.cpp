/*
This file (ScheduleSubTypeData.cpp) is generated
*/
#include "ScheduleSubTypeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ScheduleSubTypeData*>* ScheduleSubTypeData::p_sharedDictionary = nullptr;

string ScheduleSubTypeData::getId() const
{
	return to_string(p_scheduleSubTypeId);
}

string ScheduleSubTypeData::getScheduleSubTypeId() const
{
	return p_scheduleSubTypeId;
}

string ScheduleSubTypeData::getName() const
{
	string localId = "scheduleSubType_name_" + to_string(p_scheduleSubTypeId);
	return LocalizationHelper::getLocalization(localId);
}

ScheduleTypeData* ScheduleSubTypeData::getScheduleTypeData() const
{
	return ScheduleTypeData::getScheduleTypeDataById(p_scheduleTypeId);
}

string ScheduleSubTypeData::getScheduleTypeId() const
{
	return p_scheduleTypeId;
}

string ScheduleSubTypeData::description() const
{
	string desc = "scheduleSubTypeData = {\n";
	desc += "\tscheduleSubTypeId : " + to_string(p_scheduleSubTypeId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tscheduleType : " + to_string(p_scheduleTypeId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ScheduleSubTypeData*>* ScheduleSubTypeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ScheduleSubTypeData*>();
		static string resPath = "res/base/data/scheduleSubType.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ScheduleSubTypeData* scheduleSubTypeData = new ScheduleSubTypeData();
				scheduleSubTypeData->p_scheduleSubTypeId = buffer->getString();
				scheduleSubTypeData->p_scheduleTypeId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ScheduleSubTypeData*>(scheduleSubTypeData->p_scheduleSubTypeId, scheduleSubTypeData));
			}
		}
	}
	return p_sharedDictionary;
}

ScheduleSubTypeData* ScheduleSubTypeData::getScheduleSubTypeDataById(const string& scheduleSubTypeId)
{
	if (ScheduleSubTypeData::getSharedDictionary()->count(scheduleSubTypeId)) {
		return ScheduleSubTypeData::getSharedDictionary()->at(scheduleSubTypeId);
	}
	return nullptr;
}

string ScheduleSubTypeData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "scheduleSubTypeId") {
		return to_string(this->getScheduleSubTypeId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "scheduleType") {
		return to_string(this->getScheduleTypeId());
	}
	CCLOGWARN("Couldn't recognize %s in ScheduleSubTypeData", fieldName.c_str());
	return "";
}

BaseData* ScheduleSubTypeData::getDataByField(const string & fieldName) const
{
	if (fieldName == "scheduleType") {
		return this->getScheduleTypeData();
	}
	CCLOGWARN("Couldn't recognize %s in ScheduleSubTypeData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ScheduleSubTypeData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ScheduleSubTypeData", fieldName.c_str());
	return vector<BaseData *>();
}

