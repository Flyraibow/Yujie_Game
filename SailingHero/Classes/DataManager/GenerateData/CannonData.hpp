/*
This file (CannonData.hpp) is generated at 2018-07-11 01:50:01
*/
#ifndef CannonData_hpp
#define CannonData_hpp
#include <unordered_map>

using namespace std;
class CannonData
{
private:
	string p_cannonId;
	string p_iconId;
	int p_milltaryValue;
	int p_price;
	int p_range;
	int p_power;
public:
	string getCannonId() const;
	string getCannonName() const;
	string getCannonDescription() const;
	cocos2d::Sprite* getIcon() const;
	string getIconId() const;
	int getMilltaryValue() const;
	int getPrice() const;
	int getRange() const;
	int getPower() const;
	string description() const;
	static unordered_map<string, CannonData*>* getSharedDictionary();
	static CannonData* getCannonDataById(const string& cannonId);
};
#endif
