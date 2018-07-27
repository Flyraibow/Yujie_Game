/*
This file (GameData.hpp) is generated
*/
#ifndef GameData_hpp
#define GameData_hpp

#include <string>

class GameData
{
private:
	static GameData* p_sharedData;
	int p_year;
	int p_month;
	int p_day;
public:
	int getYear() const;
	void setYear(int year);
	int getMonth() const;
	void setMonth(int month);
	int getDay() const;
	void setDay(int day);
	std::string description() const;
	static GameData* getSharedInstance();
	static bool saveData(const std::string & path);
	static bool loadData(const std::string & path);
	static bool clearData();
};
#endif
