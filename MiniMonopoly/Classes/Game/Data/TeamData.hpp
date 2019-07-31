//
//  TeamData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef TeamData_hpp
#define TeamData_hpp

#include "cocos2d.h"

class CityData;
class GuildData;

using namespace std;

class TeamData
{
private:
  GuildData* p_guildData;
  CityData* p_currentCity;
  cocos2d::Vec2 p_currentPos;
  string p_teamName;
public:
  TeamData(GuildData* guildData);
  void setName(const string &name) {p_teamName = name;};
  void setCurrCity(CityData* currentCity) {p_currentCity = currentCity;};
  string getName() const {return p_teamName;};
  static TeamData* createTeam(GuildData* guildData, CityData* cityData);
  static int getCreatTeamPrice(GuildData* guildData);
};

#endif /* TeamData_hpp */
