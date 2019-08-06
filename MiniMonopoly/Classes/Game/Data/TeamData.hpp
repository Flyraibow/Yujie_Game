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
class GoodsData;
class GuildData;
class CityGoodsData;

using namespace std;

class TeamGoodsData
{
private:
  const GoodsData *p_goodsData;
  int p_level;
  int p_num;
  int p_price;
  CityData* p_fromCity;
public:
  TeamGoodsData(CityGoodsData* cityGoodData, int number);
  int getNum() const {return p_num;};
};

class TeamData
{
private:
  string p_id;
  GuildData* p_guildData;
  CityData* p_currentCity;
  cocos2d::Vec2 p_currentPos;
  string p_teamName;
  int p_maxCapacity;
  vector<TeamGoodsData *> p_goodsList;
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
  vector<TeamGoodsData *> getGoodsList() const {return p_goodsList;};
  int getCurrentLoads() const;
  
  static TeamData* createTeam(GuildData* guildData, CityData* cityData);
  static int getCreatTeamPrice(GuildData* guildData);
};

#endif /* TeamData_hpp */
