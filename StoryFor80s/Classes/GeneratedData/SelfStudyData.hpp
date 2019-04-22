/*
This file (SelfStudyData.hpp) is generated
*/
#ifndef SelfStudyData_hpp
#define SelfStudyData_hpp
#include <map>
#include "BaseData.h"
#include "ProficiencyData.hpp"
#include "AttributeData.hpp"


class SelfStudyData: public BaseData
{
private:
	static map<string, SelfStudyData*>* p_sharedDictionary;
	string p_selfStudyId;
	string p_condition;
	string p_proficiencyIdId;
	int p_addProficiency;
	map<string, int> p_attributeChangeMap;
public:
	string getId() const;
	string getSelfStudyId() const;
	string getName() const;
	string getCondition() const;
	ProficiencyData* getProficiencyIdData() const;
	string getProficiencyIdId() const;
	int getAddProficiency() const;
	string getDescription() const;
	vector<BaseData *> getAttributeChangeList() const;
	map<string, int> getAttributeChangeMap() const;
	string description() const;
	static const map<string, SelfStudyData*>* getSharedDictionary();
	static SelfStudyData* getSelfStudyDataById(const string& selfStudyId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
