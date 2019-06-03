/*
This file (DateData.hpp) is generated
*/
#ifndef DateData_hpp
#define DateData_hpp
#include <map>
#include "BaseData.h"


class DateData: public BaseData
{
private:
	static map<string, DateData*>* p_sharedDictionary;
	string p_dateId;
	int p_year;
	int p_month;
	int p_day;
public:
	string getId() const;
	string getDateId() const;
	int getYear() const;
	void setYear(int year);
	int getMonth() const;
	void setMonth(int month);
	int getDay() const;
	void setDay(int day);
	string description() const;
	static const map<string, DateData*>* getSharedDictionary();
	static DateData* getDateDataById(const string& dateId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
