/*
This file (SelectableScheduleData.hpp) is generated
*/
#ifndef SelectableScheduleData_hpp
#define SelectableScheduleData_hpp
#include <map>
#include "BaseData.h"
#include "ScheduleTypeData.hpp"
#include "ScheduleSubTypeData.hpp"
#include "ProficiencyData.hpp"
#include "AttributeData.hpp"


class SelectableScheduleData: public BaseData
{
private:
	static map<string, SelectableScheduleData*>* p_sharedDictionary;
	string p_scheduleId;
	string p_typeId;
	string p_subTypeId;
	string p_condition;
	int p_addictions;
	string p_proficiencyId;
	int p_addProficiency;
	map<string, int> p_attributeChangeMap;
public:
	string getId() const;
	string getScheduleId() const;
	string getName() const;
	ScheduleTypeData* getTypeData() const;
	string getTypeId() const;
	ScheduleSubTypeData* getSubTypeData() const;
	string getSubTypeId() const;
	string getCondition() const;
	int getAddictions() const;
	ProficiencyData* getProficiencyData() const;
	string getProficiencyId() const;
	int getAddProficiency() const;
	string getDescription() const;
	vector<BaseData *> getAttributeChangeList() const;
	map<string, int> getAttributeChangeMap() const;
	string description() const;
	static const map<string, SelectableScheduleData*>* getSharedDictionary();
	static SelectableScheduleData* getSelectableScheduleDataById(const string& scheduleId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
