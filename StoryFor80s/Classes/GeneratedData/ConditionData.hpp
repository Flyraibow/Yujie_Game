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
	string p_leftType;
	string p_leftParameter;
	string p_compareFunction;
	string p_rightType;
	string p_rightParameter;
public:
	string getId() const;
	string getConditionId() const;
	string getLeftType() const;
	string getLeftParameter() const;
	string getCompareFunction() const;
	string getRightType() const;
	string getRightParameter() const;
	string description() const;
	static const map<string, ConditionData*>* getSharedDictionary();
	static ConditionData* getConditionDataById(const string& conditionId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
