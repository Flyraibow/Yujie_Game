/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp
#include "CityData.hpp"
#include "GuildData.hpp"


class GameData
{
private:
	static GameData* p_sharedData;
	int p_year;
	int p_month;
	int p_day;
	string p_cityIdId;
	string p_guildIdId;
public:
	int getYear() const;
	void setYear(int year);
	int getMonth() const;
	void setMonth(int month);
	int getDay() const;
	void setDay(int day);
	CityData* getCityIdData() const;
	string getCityIdId() const;
	void setCityIdId(string cityId);
	GuildData* getGuildIdData() const;
	string getGuildIdId() const;
	void setGuildIdId(string guildId);
	string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
