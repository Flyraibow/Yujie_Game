/*
This file (CannonData.hpp) is generated
*/
#ifndef CannonData_hpp
#define CannonData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class CannonData: public BaseData
{
private:
	static map<int, CannonData*>* p_sharedDictionary;
	int p_cannonId;
	string p_iconId;
	int p_milltaryValue;
	int p_price;
	int p_range;
	int p_power;
public:
	string getId() const;
	int getCannonId() const;
	string getCannonName() const;
	string getCannonDescription() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	int getMilltaryValue() const;
	int getPrice() const;
	int getRange() const;
	int getPower() const;
	string description() const;
	static map<int, CannonData*>* getSharedDictionary();
	static CannonData* getCannonDataById(int cannonId);
	static CannonData* getCannonDataById(const string& cannonId);
};
#endif
