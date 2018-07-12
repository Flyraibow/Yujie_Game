/*
This file (ZodiacData.hpp) is generated
*/
#ifndef ZodiacData_hpp
#define ZodiacData_hpp
#include <unordered_map>

using namespace std;
class ZodiacData
{
private:
	static unordered_map<string, ZodiacData*>* p_sharedDictionary;
	string p_zodiacId;
	string p_iconId;
	int p_startMonth;
	int p_startDate;
	int p_endMonth;
	int p_endDate;
public:
	string getZodiacId() const;
	string getZodiacName() const;
	cocos2d::Sprite* getIcon() const;
	string getIconId() const;
	int getStartMonth() const;
	int getStartDate() const;
	int getEndMonth() const;
	int getEndDate() const;
	string description() const;
	static unordered_map<string, ZodiacData*>* getSharedDictionary();
	static ZodiacData* getZodiacDataById(const string& zodiacId);
};
#endif
