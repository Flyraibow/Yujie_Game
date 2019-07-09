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
	bool p_selecatable;
	int p_point;
	int p_salary;
public:
	string getId() const;
	string getFatherJobId() const;
	string getName() const;
	bool getSelecatable() const;
	int getPoint() const;
	int getSalary() const;
	string getDescription() const;
	string description() const;
	static const map<string, FatherJobData*>* getSharedDictionary();
	static FatherJobData* getFatherJobDataById(const string& fatherJobId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
