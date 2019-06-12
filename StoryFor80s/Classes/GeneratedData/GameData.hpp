/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp
#include "BaseData.h"
#include "DateData.hpp"
#include "DateData.hpp"
#include "FatherJobData.hpp"
#include "SchoolData.hpp"


class GameData: public BaseData
{
private:
	static GameData* p_sharedData;
	string p_gameDateId;
	string p_firstName;
	string p_lastName;
	string p_myBirthDayId;
	string p_parentJobId;
	string p_schoolId;
	bool p_hasTalkedToParent;
public:
	DateData* getGameDateData() const;
	string getGameDateId() const;
	string getFirstName() const;
	void setFirstName(string firstName);
	string getLastName() const;
	void setLastName(string lastName);
	DateData* getMyBirthDayData() const;
	string getMyBirthDayId() const;
	FatherJobData* getParentJobData() const;
	string getParentJobId() const;
	void setParentJobId(string parentJob);
	SchoolData* getSchoolData() const;
	string getSchoolId() const;
	void setSchoolId(string school);
	bool getHasTalkedToParent() const;
	void setHasTalkedToParent(bool hasTalkedToParent);
	string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
