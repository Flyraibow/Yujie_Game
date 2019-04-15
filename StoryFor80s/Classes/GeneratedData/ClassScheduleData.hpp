/*
This file (ClassScheduleData.hpp) is generated
*/
#ifndef ClassScheduleData_hpp
#define ClassScheduleData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class ClassScheduleData
{
private:
	static map<string, map<string,string>>* p_sharedDictionary;
public:
	static const map<string, map<string,string>>* getSharedDictionary();
	static string getClassSchedule(string date, string schooId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
