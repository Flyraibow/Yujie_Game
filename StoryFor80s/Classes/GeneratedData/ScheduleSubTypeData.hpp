/*
This file (ScheduleSubTypeData.hpp) is generated
*/
#ifndef ScheduleSubTypeData_hpp
#define ScheduleSubTypeData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"


class ScheduleSubTypeData: public BaseData
{
private:
	static map<string, ScheduleSubTypeData*>* p_sharedDictionary;
	string p_scheduleSubTypeId;
	string p_scheduleTypeId;
public:
	string getId() const;
	string getScheduleSubTypeId() const;
	string getName() const;
	ScheduleTypeData* getScheduleTypeData() const;
	string getScheduleTypeId() const;
	string description() const;
	static const map<string, ScheduleSubTypeData*>* getSharedDictionary();
	static ScheduleSubTypeData* getScheduleSubTypeDataById(const string& scheduleSubTypeId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
