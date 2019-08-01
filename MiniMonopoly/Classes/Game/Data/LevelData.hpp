//
//  LevelData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef LevelData_hpp
#define LevelData_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "CityData.hpp"
#include "GuildData.hpp"

using namespace std;

class LevelData
{
private:
  string p_id;
  string p_name;
  string p_mapPath;
  string p_iconPath;
  vector<CityData *> p_cities;
  vector<GuildData *> p_guildList;
  GuildData* p_myGuild;
  unordered_map<string, CityData *> p_citiesMap;
  
public:
  LevelData(const string &id);
  string getMapPath() const {return p_mapPath;};
  vector<CityData *> getCities() const {return p_cities;};
  CityData* getCityData(const string &id) const;
  GuildData* getMyGuild() const {return p_myGuild;};
  vector<GuildData *> getAllGuilds() const {return p_guildList;};
  ~LevelData();
};

#endif /* LevelData_hpp */
