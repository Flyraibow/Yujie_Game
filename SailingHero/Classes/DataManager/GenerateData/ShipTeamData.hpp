/*
This file (ShipTeamData.hpp) is generated
*/
#ifndef ShipTeamData_hpp
#define ShipTeamData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "HeroData.hpp"
#include "ShipData.hpp"

class CityData;

class ShipTeamData: public BaseData
{
private:
	static map<int, ShipTeamData*>* p_sharedDictionary;
	int p_shipTeamId;
	string p_leaderId;
	bool p_isActive;
	bool p_isDismissed;
	bool p_hasInformation;
	bool p_hasMet;
	vector<string> p_shipIdVector;
	bool p_isOut;
	double p_posX;
	double p_posY;
	string p_cityId;
	int p_tireness;
public:
	string getId() const;
	int getShipTeamId() const;
	void setShipTeamId(int shipTeamId);
	HeroData* getLeaderData() const;
	string getLeaderId() const;
	bool getIsActive() const;
	void setIsActive(bool isActive);
	bool getIsDismissed() const;
	void setIsDismissed(bool isDismissed);
	bool getHasInformation() const;
	void setHasInformation(bool hasInformation);
	bool getHasMet() const;
	void setHasMet(bool hasMet);
	vector<ShipData*> getShipDataVector() const;
	vector<string> getShipIdVector() const;
	void setShipIdVector(vector<string> ship);
	bool getIsOut() const;
	void setIsOut(bool isOut);
	double getPosX() const;
	void setPosX(double posX);
	double getPosY() const;
	void setPosY(double posY);
	CityData* getCityData() const;
	string getCityId() const;
	void setCityId(string city);
	int getTireness() const;
	void setTireness(int tireness);
	string description() const;
	static const map<int, ShipTeamData*>* getSharedDictionary();
	static ShipTeamData* getShipTeamDataById(int shipTeamId);
	static ShipTeamData* getShipTeamDataById(const string& shipTeamId);
	static ShipTeamData* registerShipTeamData(string leader, bool isActive, bool isDismissed, bool hasInformation, bool hasMet, vector<string> ship, bool isOut, double posX, double posY, string city, int tireness);
	static bool removeShipTeamDataById(int shipTeamId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
