/*
This file (ScheduleData.hpp) is generated
*/
#ifndef ScheduleData_hpp
#define ScheduleData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"
#include "SchoolStudyData.hpp"


class ScheduleData: public BaseData
{
private:
	static map<string, ScheduleData*>* p_sharedDictionary;
	string p_scheduleId;
	int p_priority;
	string p_condition;
	int p_year;
	int p_month;
	string p_typeId;
	string p_schoolStudyId;
public:
	string getId() const;
	string getScheduleId() const;
	int getPriority() const;
	string getCondition() const;
	int getYear() const;
	int getMonth() const;
	ScheduleTypeData* getTypeData() const;
	string getTypeId() const;
	SchoolStudyData* getSchoolStudyData() const;
	string getSchoolStudyId() const;
	string description() const;
	static const map<string, ScheduleData*>* getSharedDictionary();
	static ScheduleData* getScheduleDataById(const string& scheduleId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
