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
	static map<int, map<string,string>>* p_sharedDictionary;
public:
	static const map<int, map<string,string>>* getSharedDictionary();
	static string getClassSchedule(int date, string schooId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
};
#endif
