/*
This file (ScheduleData.cpp) is generated
*/
#include "ScheduleData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, ScheduleData*>* ScheduleData::p_sharedDictionary = nullptr;

string ScheduleData::getId() const
{
	return to_string(p_scheduleId);
}

string ScheduleData::getScheduleId() const
{
	return p_scheduleId;
}

int ScheduleData::getPriority() const
{
	return p_priority;
}

string ScheduleData::getCondition() const
{
	return p_condition;
}

int ScheduleData::getYear() const
{
	return p_year;
}

int ScheduleData::getMonth() const
{
	return p_month;
}

SchoolData* ScheduleData::getSchoolData() const
{
	return SchoolData::getSchoolDataById(p_schoolId);
}

string ScheduleData::getSchoolId() const
{
	return p_schoolId;
}

ScheduleTypeData* ScheduleData::getTypeData() const
{
	return ScheduleTypeData::getScheduleTypeDataById(p_typeId);
}

string ScheduleData::getTypeId() const
{
	return p_typeId;
}

vector<SchoolStudyData*> ScheduleData::getSchoolStudyDataVector() const
{
	vector<SchoolStudyData*> resultVector;
	for (auto objId : p_schoolStudyIdVector) {
		resultVector.push_back(SchoolStudyData::getSchoolStudyDataById(objId));
	}
	return resultVector;
}

vector<string> ScheduleData::getSchoolStudyIdVector() const
{
	return p_schoolStudyIdVector;
}

string ScheduleData::description() const
{
	string desc = "scheduleData = {\n";
	desc += "\tscheduleId : " + to_string(p_scheduleId) + "\n";
	desc += "\tpriority : " + to_string(p_priority) + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tschool : " + to_string(p_schoolId) + "\n";
	desc += "\ttype : " + to_string(p_typeId) + "\n";
	desc += "\tschoolStudy : " + to_string(p_schoolStudyIdVector) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ScheduleData*>* ScheduleData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ScheduleData*>();
		static string resPath = "res/base/data/schedule.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ScheduleData* scheduleData = new ScheduleData();
				scheduleData->p_scheduleId = buffer->getString();
				scheduleData->p_priority = buffer->getInt();
				scheduleData->p_condition = buffer->getString();
				scheduleData->p_year = buffer->getInt();
				scheduleData->p_month = buffer->getInt();
				scheduleData->p_schoolId = buffer->getString();
				scheduleData->p_typeId = buffer->getString();
				auto schoolStudyCount = buffer->getLong();
				for (int j = 0; j < schoolStudyCount; ++j) {
					scheduleData->p_schoolStudyIdVector.push_back(buffer->getString());
				}
				p_sharedDictionary->insert(pair<string, ScheduleData*>(scheduleData->p_scheduleId, scheduleData));
			}
		}
	}
	return p_sharedDictionary;
}

ScheduleData* ScheduleData::getScheduleDataById(const string& scheduleId)
{
	if (ScheduleData::getSharedDictionary()->count(scheduleId)) {
		return ScheduleData::getSharedDictionary()->at(scheduleId);
	}
	return nullptr;
}

string ScheduleData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "scheduleId") {
		return to_string(this->getScheduleId());
	} else if (fieldName == "priority") {
		return to_string(this->getPriority());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "year") {
		return to_string(this->getYear());
	} else if (fieldName == "month") {
		return to_string(this->getMonth());
	} else if (fieldName == "school") {
		return to_string(this->getSchoolId());
	} else if (fieldName == "type") {
		return to_string(this->getTypeId());
	} else if (fieldName == "schoolStudy") {
		return to_string(this->getSchoolStudyIdVector());
	}
	CCLOGWARN("Couldn't recognize %s in ScheduleData", fieldName.c_str());
	return "";
}

BaseData* ScheduleData::getDataByField(const string & fieldName) const
{
	if (fieldName == "school") {
		return this->getSchoolData();
	} else if (fieldName == "type") {
		return this->getTypeData();
	}
	CCLOGWARN("Couldn't recognize %s in ScheduleData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ScheduleData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ScheduleData", fieldName.c_str());
	return vector<BaseData *>();
}

