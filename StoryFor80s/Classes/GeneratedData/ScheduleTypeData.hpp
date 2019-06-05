/*
This file (ScheduleTypeData.hpp) is generated
*/
#ifndef ScheduleTypeData_hpp
#define ScheduleTypeData_hpp
#include <map>
#include "BaseData.h"


class ScheduleTypeData: public BaseData
{
private:
	static map<string, ScheduleTypeData*>* p_sharedDictionary;
	string p_scheduleTypeId;
	bool p_selectable;
public:
	string getId() const;
	string getScheduleTypeId() const;
	string getName() const;
	bool getSelectable() const;
	string description() const;
	static const map<string, ScheduleTypeData*>* getSharedDictionary();
	static ScheduleTypeData* getScheduleTypeDataById(const string& scheduleTypeId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
