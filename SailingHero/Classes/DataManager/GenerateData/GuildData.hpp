/*
This file (GuildData.hpp) is generated
*/
#ifndef GuildData_hpp
#define GuildData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "HeroData.hpp"
#include "ShipTeamData.hpp"


class GuildData: public BaseData
{
private:
	static map<int, GuildData*>* p_sharedDictionary;
	int p_guildId;
	string p_guildName;
	string p_leaderId;
	vector<string> p_shipTeamIdVector;
	int p_style;
	int p_money;
public:
	string getId() const;
	int getGuildId() const;
	void setGuildName(string guildName);
	string getGuildName() const;
	HeroData* getLeaderData() const;
	string getLeaderId() const;
	vector<ShipTeamData*> getShipTeamDataVector() const;
	vector<string> getShipTeamIdVector() const;
	void setShipTeamIdVector(vector<string> shipTeam);
	int getStyle() const;
	int getMoney() const;
	void setMoney(int money);
	string description() const;
	static const map<int, GuildData*>* getSharedDictionary();
	static GuildData* getGuildDataById(int guildId);
	static GuildData* getGuildDataById(const string& guildId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
