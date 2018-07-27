/*
This file (ZodiacData.hpp) is generated
*/
#ifndef ZodiacData_hpp
#define ZodiacData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class ZodiacData: public BaseData
{
private:
	static map<int, ZodiacData*>* p_sharedDictionary;
	int p_zodiacId;
	string p_iconId;
	int p_startMonth;
	int p_startDate;
	int p_endMonth;
	int p_endDate;
public:
	string getId() const;
	int getZodiacId() const;
	string getZodiacName() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	int getStartMonth() const;
	int getStartDate() const;
	int getEndMonth() const;
	int getEndDate() const;
	string description() const;
	static map<int, ZodiacData*>* getSharedDictionary();
	static ZodiacData* getZodiacDataById(int zodiacId);
	static ZodiacData* getZodiacDataById(const string& zodiacId);
};
#endif
