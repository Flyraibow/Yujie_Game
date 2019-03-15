/*
This file (ConditionCalculationData.hpp) is generated
*/
#ifndef ConditionCalculationData_hpp
#define ConditionCalculationData_hpp
#include <map>
#include "BaseData.h"
#include "ConditionData.hpp"


class ConditionCalculationData: public BaseData
{
private:
	static map<string, ConditionCalculationData*>* p_sharedDictionary;
	string p_conditionCalculationId;
	string p_conditionId;
	string p_yesType;
	string p_yesParameter;
	string p_noType;
	string p_noParameter;
public:
	string getId() const;
	string getConditionCalculationId() const;
	ConditionData* getConditionData() const;
	string getConditionId() const;
	string getYesType() const;
	string getYesParameter() const;
	string getNoType() const;
	string getNoParameter() const;
	string description() const;
	static const map<string, ConditionCalculationData*>* getSharedDictionary();
	static ConditionCalculationData* getConditionCalculationDataById(const string& conditionCalculationId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
};
#endif
