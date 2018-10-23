/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp
#include "BaseData.h"
#include <set>
#include "CityData.hpp"
#include "GuildData.hpp"
#include "StoryData.hpp"


class GameData: public BaseData
{
private:
	static GameData* p_sharedData;
	int p_year;
	int p_month;
	int p_day;
	string p_cityId;
	string p_guildId;
	set<string> p_experiencedStoriesIdSet;
public:
	int getYear() const;
	void setYear(int year);
	int getMonth() const;
	void setMonth(int month);
	int getDay() const;
	void setDay(int day);
	CityData* getCityData() const;
	string getCityId() const;
	void setCityId(string city);
	GuildData* getGuildData() const;
	string getGuildId() const;
	void setGuildId(string guild);
	set<StoryData*> getExperiencedStoriesDataSet() const;
	set<string> getExperiencedStoriesIdSet() const;
	void setExperiencedStoriesIdSet(set<string> experiencedStories);
	string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
