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
  string p_id;
  GuildData* p_guildData;
  CityData* p_currentCity;
  cocos2d::Vec2 p_currentPos;
  string p_teamName;
public:
  TeamData(GuildData* guildData);
  void setId(const string &id) {p_id = id;};
  string getId() const {return p_id;};
  void setName(const string &name) {p_teamName = name;};
  CityData* getCurrCity() const {return p_currentCity;};
  cocos2d::Vec2 getCurrPosition() const {return p_currentPos;};
  void setCurrCity(CityData* currentCity) {p_currentCity = currentCity;};
  GuildData* getGuild() const {return p_guildData;};
  string getName() const {return p_teamName;};
  static TeamData* createTeam(GuildData* guildData, CityData* cityData);
  static int getCreatTeamPrice(GuildData* guildData);
};

#endif /* TeamData_hpp */
