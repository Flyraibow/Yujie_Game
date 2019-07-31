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

class GuildData
{
private:
  string p_id;
  string p_guildId;
  string p_guildName;
  unordered_map<CityData *, int> p_cityControls;
  int p_money;
  cocos2d::Color3B p_color;
public:
  GuildData(const string &id);
  string getId() const {return p_id;};
  int getMoney() const {return p_money;};
  string getName() const {return p_guildName;};
  void setId(const string &id) {p_id = id;};
  void setMoney(int money) {p_money = money;};
  cocos2d::Color3B getColor() const {return p_color;};
  void setCityControl(CityData *city, int value) {p_cityControls[city] = value;};
  unordered_map<CityData *, int> getCityControls() {return p_cityControls;};
  static GuildData* loadGuildDataWithOverrideJson(const nlohmann::json &guildJson);
};

#endif /* GuildData_hpp */
