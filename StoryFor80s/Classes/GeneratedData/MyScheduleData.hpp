/*
This file (MyScheduleData.hpp) is generated
*/
#ifndef MyScheduleData_hpp
#define MyScheduleData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"
#include "SelectableScheduleData.hpp"


class MyScheduleData: public BaseData
{
private:
	static map<string, MyScheduleData*>* p_sharedDictionary;
	string p_myScheduleId;
	string p_condition;
	bool p_locked;
	string p_typeId;
	string p_scheduleId;
public:
	string getId() const;
	string getMyScheduleId() const;
	string getCondition() const;
	bool getLocked() const;
	void setLocked(bool locked);
	ScheduleTypeData* getTypeData() const;
	string getTypeId() const;
	void setTypeId(string type);
	SelectableScheduleData* getScheduleData() const;
	string getScheduleId() const;
	void setScheduleId(string schedule);
	string description() const;
	static const map<string, MyScheduleData*>* getSharedDictionary();
	static MyScheduleData* getMyScheduleDataById(const string& myScheduleId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
