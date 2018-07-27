/*
This file (GuildData.hpp) is generated
*/
#ifndef GuildData_hpp
#define GuildData_hpp
#include <map>
#include "BaseData.h"
#include "HeroData.hpp"



class GuildData: public BaseData
{
private:
	static map<int, GuildData*>* p_sharedDictionary;
	int p_guildId;
	string p_guildName;
	string p_leaderId;
	int p_style;
	int p_money;
public:
	string getId() const;
	int getGuildId() const;
	void setGuildName(string guildName);
	string getGuildName() const;
	HeroData* getLeaderData() const;
	string getLeaderId() const;
	int getStyle() const;
	int getMoney() const;
	void setMoney(int money);
	string description() const;
	static map<int, GuildData*>* getSharedDictionary();
	static GuildData* getGuildDataById(int guildId);
	static GuildData* getGuildDataById(const string& guildId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
