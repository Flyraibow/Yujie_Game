/*
This file (ShipStyleData.hpp) is generated
*/
#ifndef ShipStyleData_hpp
#define ShipStyleData_hpp
#include <map>
#include "BaseData.h"
#include <set>
#include "ShipSizeData.hpp"
#include "CultureData.hpp"


class ShipStyleData: public BaseData
{
private:
	static map<int, ShipStyleData*>* p_sharedDictionary;
	int p_shipStyleId;
	string p_shipSizeId;
	string p_iconId;
	int p_developValue;
	int p_price;
	int p_duration;
	set<string> p_sellCultureIdSet;
public:
	string getId() const;
	int getShipStyleId() const;
	string getShipStyleName() const;
	ShipSizeData* getShipSizeData() const;
	string getShipSizeId() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconPath();
	string getIconId() const;
	int getDevelopValue() const;
	int getPrice() const;
	int getDuration() const;
	set<CultureData*> getSellCultureDataSet() const;
	set<string> getSellCultureIdSet() const;
	string description() const;
	static map<int, ShipStyleData*>* getSharedDictionary();
	static ShipStyleData* getShipStyleDataById(int shipStyleId);
	static ShipStyleData* getShipStyleDataById(const string& shipStyleId);
};
#endif
