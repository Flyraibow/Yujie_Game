/*
This file (ProficiencyCategoryData.hpp) is generated
*/
#ifndef ProficiencyCategoryData_hpp
#define ProficiencyCategoryData_hpp
#include <map>
#include "BaseData.h"


class ProficiencyCategoryData: public BaseData
{
private:
	static map<string, ProficiencyCategoryData*>* p_sharedDictionary;
	string p_proficiencyCategoryId;
public:
	string getId() const;
	string getProficiencyCategoryId() const;
	string getName() const;
	string description() const;
	static const map<string, ProficiencyCategoryData*>* getSharedDictionary();
	static ProficiencyCategoryData* getProficiencyCategoryDataById(const string& proficiencyCategoryId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
