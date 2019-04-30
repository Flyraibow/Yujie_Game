/*
This file (ProficiencyData.hpp) is generated
*/
#ifndef ProficiencyData_hpp
#define ProficiencyData_hpp
#include <map>
#include "BaseData.h"


class ProficiencyData: public BaseData
{
private:
	static map<string, ProficiencyData*>* p_sharedDictionary;
	string p_proficiencyId;
	int p_value;
	int p_maxValue;
public:
	string getId() const;
	string getProficiencyId() const;
	string getName() const;
	int getValue() const;
	void setValue(int value);
	int getMaxValue() const;
	string description() const;
	static const map<string, ProficiencyData*>* getSharedDictionary();
	static ProficiencyData* getProficiencyDataById(const string& proficiencyId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif