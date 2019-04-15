/*
This file (FunctionCalculationData.hpp) is generated
*/
#ifndef FunctionCalculationData_hpp
#define FunctionCalculationData_hpp
#include <map>
#include "BaseData.h"
#include <vector>


class FunctionCalculationData: public BaseData
{
private:
	static map<string, FunctionCalculationData*>* p_sharedDictionary;
	string p_functionCalculatonId;
	string p_returnType;
	string p_functionName;
	vector<string> p_parameters;
public:
	string getId() const;
	string getFunctionCalculatonId() const;
	string getReturnType() const;
	string getFunctionName() const;
	vector<string> getParameters() const;
	string description() const;
	static const map<string, FunctionCalculationData*>* getSharedDictionary();
	static FunctionCalculationData* getFunctionCalculationDataById(const string& functionCalculatonId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
