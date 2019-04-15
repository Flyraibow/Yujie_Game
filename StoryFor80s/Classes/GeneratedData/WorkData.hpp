/*
This file (WorkData.hpp) is generated
*/
#ifndef WorkData_hpp
#define WorkData_hpp
#include <map>
#include "BaseData.h"
#include "AttributeData.hpp"
#include "PersonalityData.hpp"


class WorkData: public BaseData
{
private:
	static map<string, WorkData*>* p_sharedDictionary;
	string p_actionId;
	string p_condition;
	int p_baseSalary;
	int p_realSalary;
	int p_proficienc;
	int p_maxProficiency;
	map<string, int> p_attributeChangeMap;
	map<string, int> p_personalityChangeMap;
public:
	string getId() const;
	string getActionId() const;
	string getName() const;
	string getCondition() const;
	int getBaseSalary() const;
	int getRealSalary() const;
	void setRealSalary(int realSalary);
	int getProficienc() const;
	void setProficienc(int proficienc);
	int getMaxProficiency() const;
	vector<BaseData *> getAttributeChangeList() const;
	map<string, int> getAttributeChangeMap() const;
	vector<BaseData *> getPersonalityChangeList() const;
	map<string, int> getPersonalityChangeMap() const;
	string getDescription() const;
	string description() const;
	static const map<string, WorkData*>* getSharedDictionary();
	static WorkData* getWorkDataById(const string& actionId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
