/*
This file (SchoolStudyData.hpp) is generated
*/
#ifndef SchoolStudyData_hpp
#define SchoolStudyData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"
#include "ProficiencyData.hpp"
#include "AttributeData.hpp"


class SchoolStudyData: public BaseData
{
private:
	static map<string, SchoolStudyData*>* p_sharedDictionary;
	string p_schoolStudyId;
	string p_typeId;
	string p_proficiencyId;
	int p_addProficiency;
	map<string, int> p_attributeChangeMap;
public:
	string getId() const;
	string getSchoolStudyId() const;
	string getName() const;
	ScheduleTypeData* getTypeData() const;
	string getTypeId() const;
	ProficiencyData* getProficiencyData() const;
	string getProficiencyId() const;
	int getAddProficiency() const;
	string getDescription() const;
	vector<BaseData *> getAttributeChangeList() const;
	map<string, int> getAttributeChangeMap() const;
	string description() const;
	static const map<string, SchoolStudyData*>* getSharedDictionary();
	static SchoolStudyData* getSchoolStudyDataById(const string& schoolStudyId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
