/*
This file (SkillsData.hpp) is generated
*/
#ifndef SkillsData_hpp
#define SkillsData_hpp
#include <map>
#include "BaseData.h"
#include <set>
#include "SkillsData.hpp"


class SkillsData: public BaseData
{
private:
	static map<string, SkillsData*>* p_sharedDictionary;
	string p_skillId;
	int p_maxValue;
	int p_passValue;
	int p_value;
	set<string> p_requiresIdSet;
public:
	string getId() const;
	string getSkillId() const;
	string getName() const;
	int getMaxValue() const;
	int getPassValue() const;
	int getValue() const;
	void setValue(int value);
	set<SkillsData*> getRequiresDataSet() const;
	set<string> getRequiresIdSet() const;
	string description() const;
	static const map<string, SkillsData*>* getSharedDictionary();
	static SkillsData* getSkillsDataById(const string& skillId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
