/*
This file (ShipData.hpp) is generated
*/
#ifndef ShipData_hpp
#define ShipData_hpp
#include <map>
#include "BaseData.h"
#include "ShipStyleData.hpp"
#include "CannonData.hpp"
#include "HeroData.hpp"


class ShipData: public BaseData
{
private:
	static map<int, ShipData*>* p_sharedDictionary;
	int p_shipId;
	string p_shipName;
	string p_shipStyleId;
	string p_cannonId;
	int p_currentDuration;
	string p_leaderId;
public:
	string getId() const;
	int getShipId() const;
	void setShipId(int shipId);
	void setShipName(string shipName);
	string getShipName() const;
	ShipStyleData* getShipStyleData() const;
	string getShipStyleId() const;
	CannonData* getCannonData() const;
	string getCannonId() const;
	void setCannonId(string cannon);
	int getCurrentDuration() const;
	void setCurrentDuration(int currentDuration);
	HeroData* getLeaderData() const;
	string getLeaderId() const;
	void setLeaderId(string leader);
	string description() const;
	static const map<int, ShipData*>* getSharedDictionary();
	static ShipData* getShipDataById(int shipId);
	static ShipData* getShipDataById(const string& shipId);
	static ShipData* registerShipData(string shipName, string shipStyle, string cannon, int currentDuration, string leader);
	static bool removeShipDataById(int shipId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
