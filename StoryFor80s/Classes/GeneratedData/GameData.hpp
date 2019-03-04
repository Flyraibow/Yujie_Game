/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp
#include "BaseData.h"
#include "FatherJobData.hpp"


class GameData: public BaseData
{
private:
	static GameData* p_sharedData;
	int p_year;
	int p_month;
	int p_day;
	string p_firstName;
	string p_lastName;
	int p_birthDay;
	int p_birthMonth;
	int p_birthYear;
	string p_parentJobId;
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
	int getBirthDay() const;
	void setBirthDay(int birthDay);
	int getBirthMonth() const;
	void setBirthMonth(int birthMonth);
	int getBirthYear() const;
	void setBirthYear(int birthYear);
	FatherJobData* getParentJobData() const;
	string getParentJobId() const;
	void setParentJobId(string parentJob);
	string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
