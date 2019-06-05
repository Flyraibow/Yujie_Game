/*
This file (MyScheduleData.hpp) is generated
*/
#ifndef MyScheduleData_hpp
#define MyScheduleData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"
#include "SelfStudyData.hpp"
#include "PlayData.hpp"
#include "WorkData.hpp"


class MyScheduleData: public BaseData
{
private:
	static map<string, MyScheduleData*>* p_sharedDictionary;
	string p_myScheduleId;
	string p_condition;
	string p_typeId;
	string p_selfStudyId;
	string p_playId;
	string p_workId;
public:
	string getId() const;
	string getMyScheduleId() const;
	string getCondition() const;
	ScheduleTypeData* getTypeData() const;
	string getTypeId() const;
	void setTypeId(string type);
	SelfStudyData* getSelfStudyData() const;
	string getSelfStudyId() const;
	void setSelfStudyId(string selfStudy);
	PlayData* getPlayData() const;
	string getPlayId() const;
	void setPlayId(string play);
	WorkData* getWorkData() const;
	string getWorkId() const;
	void setWorkId(string work);
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
