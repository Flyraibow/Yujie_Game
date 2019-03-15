/*
This file (FatherJobData.hpp) is generated
*/
#ifndef FatherJobData_hpp
#define FatherJobData_hpp
#include <map>
#include "BaseData.h"


class FatherJobData: public BaseData
{
private:
	static map<string, FatherJobData*>* p_sharedDictionary;
	string p_fatherJobId;
	int p_salary;
	int p_knowledge;
public:
	string getId() const;
	string getFatherJobId() const;
	string getName() const;
	int getSalary() const;
	void setSalary(int salary);
	int getKnowledge() const;
	void setKnowledge(int knowledge);
	string getDescription() const;
	string description() const;
	static const map<string, FatherJobData*>* getSharedDictionary();
	static FatherJobData* getFatherJobDataById(const string& fatherJobId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
};
#endif
