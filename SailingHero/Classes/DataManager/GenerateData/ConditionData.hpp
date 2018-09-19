/*
This file (ConditionData.hpp) is generated
*/
#ifndef ConditionData_hpp
#define ConditionData_hpp
#include <map>
#include "BaseData.h"


class ConditionData: public BaseData
{
private:
	static map<string, ConditionData*>* p_sharedDictionary;
	string p_conditionId;
public:
	string getId() const;
	string getConditionId() const;
	string description() const;
	static const map<string, ConditionData*>* getSharedDictionary();
	static ConditionData* getConditionDataById(const string& conditionId);
	string getFieldValue(const string & fieldName);
};
#endif
