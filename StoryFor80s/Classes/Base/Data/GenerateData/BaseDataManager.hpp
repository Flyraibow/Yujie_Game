/*
This file (BaseDataManager.hpp) is generated
*/
#ifndef BaseDataManager_hpp
#define BaseDataManager_hpp
#include "ConditionData.hpp"
#include "ConditionCalculationData.hpp"
#include "FunctionCalculationData.hpp"
#include "GameData.hpp"


class BaseDataManager
{
private:
public:
	static ConditionData* getConditionDataById(const string& conditionId);
	static ConditionCalculationData* getConditionCalculationDataById(const string& conditionCalculationId);
	static FunctionCalculationData* getFunctionCalculationDataById(const string& functionCalculatonId);
	static GameData* getGameData();
	static bool saveData(string fileName);
	static bool loadData(string fileName);
	static bool clearData();
	static BaseData * getData(const string & dataSet, const string & id);
	static string getDataField(const string & dataSet, const string & id, const string & fieldName);
	static void setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value);
};
#endif
