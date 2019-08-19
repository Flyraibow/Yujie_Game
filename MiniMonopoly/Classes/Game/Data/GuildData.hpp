//
//  GuildData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef GuildData_hpp
#define GuildData_hpp

#include <stdio.h>
#include "json.hpp"
#include "cocos2d.h"

using namespace std;

class CityData;
class TeamData;


typedef std::function<void()> mmGuildMoneyChangeCallback;

class GuildData
{
private:
  string p_id;
  string p_guildId;
  string p_guildName;
  unordered_map<CityData *, int> p_cityControls;
  int p_money;
  cocos2d::Color3B p_color;
  bool p_isPlayer;
  vector<TeamData *> p_teamList;
  unordered_map<string, mmGuildMoneyChangeCallback> p_moneyChangeCallbacks;
public:
  GuildData(const string &id);
  string getId() const {return p_id;};
  int getMoney() const {return p_money;};
  void setIsPlayer(bool isPlayer) {p_isPlayer = isPlayer;};
  bool isPlayer() const {return p_isPlayer;};
  string getName() const {return p_guildName;};
  void setId(const string &id) {p_id = id;};
  void setMoney(int money);
  void addTeam(TeamData *team) {p_teamList.push_back(team);};
  vector<TeamData *> getTeams() const {return p_teamList;};
  cocos2d::Color3B getColor() const {return p_color;};
  void setCityControl(CityData *city, int value) {p_cityControls[city] = value;};
  unordered_map<CityData *, int> getCityControls() {return p_cityControls;};
  static GuildData* loadGuildDataWithOverrideJson(const nlohmann::json &guildJson);
  
  void addMoneyChangeCallback(const string& key, mmGuildMoneyChangeCallback callback);
  void removeMoneyChangeCallback(const string& key);
};

#endif /* GuildData_hpp */
