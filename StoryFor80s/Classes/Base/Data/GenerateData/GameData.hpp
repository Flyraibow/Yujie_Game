/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp
#include "BaseData.h"


class GameData: public BaseData
{
private:
	static GameData* p_sharedData;
	int p_year;
	int p_month;
	int p_day;
	string p_firstName;
	string p_lastName;
public:
	int getYear() const;
	void setYear(int year);
	int getMonth() const;
	void setMonth(int month);
	int getDay() const;
	void setDay(int day);
	string getFirstName() const;
	void setFirstName(string firstName);
	string getLastName() const;
	void setLastName(string lastName);
	string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
