/*
This file (PersonalityData.hpp) is generated
*/
#ifndef PersonalityData_hpp
#define PersonalityData_hpp
#include <map>
#include "BaseData.h"


class PersonalityData: public BaseData
{
private:
	static map<string, PersonalityData*>* p_sharedDictionary;
	string p_attributeId;
	int p_value;
public:
	string getId() const;
	string getAttributeId() const;
	string getName() const;
	int getValue() const;
	void setValue(int value);
	string description() const;
	static const map<string, PersonalityData*>* getSharedDictionary();
	static PersonalityData* getPersonalityDataById(const string& attributeId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
