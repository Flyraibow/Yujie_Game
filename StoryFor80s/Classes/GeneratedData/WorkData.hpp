/*
This file (WorkData.hpp) is generated
*/
#ifndef WorkData_hpp
#define WorkData_hpp
#include <map>
#include "BaseData.h"


class WorkData: public BaseData
{
private:
	static map<string, WorkData*>* p_sharedDictionary;
	string p_actionId;
	int p_salary;
	int p_proficienc;
public:
	string getId() const;
	string getActionId() const;
	string getName() const;
	int getSalary() const;
	int getProficienc() const;
	void setProficienc(int proficienc);
	string description() const;
	static const map<string, WorkData*>* getSharedDictionary();
	static WorkData* getWorkDataById(const string& actionId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
