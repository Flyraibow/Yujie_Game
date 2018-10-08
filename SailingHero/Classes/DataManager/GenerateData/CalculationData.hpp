/*
This file (CalculationData.hpp) is generated
*/
#ifndef CalculationData_hpp
#define CalculationData_hpp
#include <map>
#include "BaseData.h"
#include "ConditionData.hpp"


class CalculationData: public BaseData
{
private:
	static map<string, CalculationData*>* p_sharedDictionary;
	string p_calculationId;
	string p_conditionId;
	string p_yesType;
	string p_yesParameter;
	string p_noType;
	string p_noParameter;
public:
	string getId() const;
	string getCalculationId() const;
	ConditionData* getConditionData() const;
	string getConditionId() const;
	string getYesType() const;
	string getYesParameter() const;
	string getNoType() const;
	string getNoParameter() const;
	string description() const;
	static const map<string, CalculationData*>* getSharedDictionary();
	static CalculationData* getCalculationDataById(const string& calculationId);
	string getFieldValue(const string & fieldName);
};
#endif
