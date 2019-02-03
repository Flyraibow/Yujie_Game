/*
This file (SHGlobalDataManager.hpp) is generated
*/
#ifndef SHGlobalDataManager_hpp
#define SHGlobalDataManager_hpp
#include "GameSavingData.hpp"


class SHGlobalDataManager
{
private:
public:
	static GameSavingData* getGameSavingDataById(int savingId);
	static GameSavingData* getGameSavingDataById(const string& savingId);
	static bool saveData(string fileName);
	static bool loadData(string fileName);
	static bool clearData();
	static BaseData * getData(const string & dataSet, const string & id);
	static string getDataField(const string & dataSet, const string & id, const string & fieldName);
	static void setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value);
};
#endif
