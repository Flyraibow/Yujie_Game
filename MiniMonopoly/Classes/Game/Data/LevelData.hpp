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
  unordered_map<string, CityData *> p_citiesMap;
  
  CityData* getCityData(const string &id);
public:
  LevelData(const string &id);
  ~LevelData();
};

#endif /* LevelData_hpp */