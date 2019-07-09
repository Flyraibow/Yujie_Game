/*
This file (BaseGlobalDataManager.hpp) is generated
*/
#ifndef BaseGlobalDataManager_hpp
#define BaseGlobalDataManager_hpp
#include "GameSavingData.hpp"
#include "GameSettingData.hpp"


class BaseGlobalDataManager
{
private:
public:
	static GameSavingData* getGameSavingDataById(int savingId);
	static GameSavingData* getGameSavingDataById(const string& savingId);
	static GameSettingData* getGameSettingData();
	static bool saveData(string fileName);
	static bool loadData(string fileName);
	static bool clearData();
	static BaseData * getData(const string & dataSet, const string & id);
	static string getDataField(const string & dataSet, const string & id, const string & fieldName);
	static void setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value);
	static vector<BaseData *> getDataList(const string & dataSet);
};
#endif
