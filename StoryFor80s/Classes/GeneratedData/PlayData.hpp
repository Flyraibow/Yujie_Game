/*
This file (PlayData.hpp) is generated
*/
#ifndef PlayData_hpp
#define PlayData_hpp
#include <map>
#include "BaseData.h"
#include "ProficiencyData.hpp"
#include "AttributeData.hpp"


class PlayData: public BaseData
{
private:
	static map<string, PlayData*>* p_sharedDictionary;
	string p_playId;
	string p_condition;
	int p_expense;
	string p_proficienceIdId;
	int p_addProficiency;
	map<string, int> p_attributeChangeMap;
public:
	string getId() const;
	string getPlayId() const;
	string getName() const;
	string getCondition() const;
	int getExpense() const;
	ProficiencyData* getProficienceIdData() const;
	string getProficienceIdId() const;
	int getAddProficiency() const;
	string getDescription() const;
	vector<BaseData *> getAttributeChangeList() const;
	map<string, int> getAttributeChangeMap() const;
	string description() const;
	static const map<string, PlayData*>* getSharedDictionary();
	static PlayData* getPlayDataById(const string& playId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
