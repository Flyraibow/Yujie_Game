/*
This file (SchoolData.hpp) is generated
*/
#ifndef SchoolData_hpp
#define SchoolData_hpp
#include <map>
#include "BaseData.h"


class SchoolData: public BaseData
{
private:
	static map<string, SchoolData*>* p_sharedDictionary;
	string p_schoolId;
	float p_studyFactor;
public:
	string getId() const;
	string getSchoolId() const;
	string getName() const;
	float getStudyFactor() const;
	string description() const;
	static const map<string, SchoolData*>* getSharedDictionary();
	static SchoolData* getSchoolDataById(const string& schoolId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
