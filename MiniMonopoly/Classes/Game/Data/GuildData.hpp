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

using namespace std;

class CityData;

class GuildData
{
private:
  string p_id;
  string p_guildId;
  string p_guildName;
  unordered_map<CityData *, int> p_cityControls;
public:
  GuildData(const string &fileName);
  string getId() const {return p_id;};
  void setId(const string &id) {p_id = id;};
  void setCityControl(CityData *city, int value) {p_cityControls[city] = value;};
  unordered_map<CityData *, int> getCityControls() {return p_cityControls;};
  static GuildData* loadGuildDataWithOverrideJson(const nlohmann::json &guildJson);
};

#endif /* GuildData_hpp */
