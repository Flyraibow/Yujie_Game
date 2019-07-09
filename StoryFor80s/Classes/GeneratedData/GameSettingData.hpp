/*
This file (GameSettingData.hpp) is generated
*/
#ifndef GameSettingData_hpp
#define GameSettingData_hpp
#include "BaseData.h"


class GameSettingData: public BaseData
{
private:
	static GameSettingData* p_sharedData;
	int p_soundVolume;
	int p_effectVolume;
public:
	int getSoundVolume() const;
	void setSoundVolume(int soundVolume);
	int getEffectVolume() const;
	void setEffectVolume(int effectVolume);
	string description() const;
	static GameSettingData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
