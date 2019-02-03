/*
This file (GameSavingData.hpp) is generated
*/
#ifndef GameSavingData_hpp
#define GameSavingData_hpp
#include <map>
#include "BaseData.h"


class GameSavingData: public BaseData
{
private:
	static map<int, GameSavingData*>* p_sharedDictionary;
	int p_savingId;
	string p_saveDescription;
	bool p_saved;
public:
	string getId() const;
	int getSavingId() const;
	void setSaveDescription(string saveDescription);
	string getSaveDescription() const;
	bool getSaved() const;
	void setSaved(bool saved);
	string description() const;
	static const map<int, GameSavingData*>* getSharedDictionary();
	static GameSavingData* getGameSavingDataById(int savingId);
	static GameSavingData* getGameSavingDataById(const string& savingId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
