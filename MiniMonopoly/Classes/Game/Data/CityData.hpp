//
//  CityData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef CityData_hpp
#define CityData_hpp

#include <stdio.h>
#include "GoodsData.hpp"
#include "json.hpp"

using namespace std;

class CityData;
class GoodsData;
class GuildData;

struct RouteData
{
  CityData* nextCity;
  float distance;
  RouteData(CityData* next, float d) {
    nextCity = next;
    distance = d;
  }
};

class CityGoodsData
{
private:
  const GoodsData *p_goodsData;
  CityData* p_city;
  int p_level;
  int p_currentNum;
  int p_maxNum;
  double p_produceSpeed;
public:
  CityGoodsData(const nlohmann::json &cityGoodsJson);
  ~CityGoodsData();
  const GoodsData* getGoodsData() const {return p_goodsData;};
  CityData* getCity() const {return p_city;};
  void setCity(CityData *city) {p_city = city;};
  string getId() const {return p_goodsData->getId();};
  int getLevel() const {return p_level;};
  int getMaxNum() const {return p_maxNum;};
  int getCurrNum() const {return p_currentNum;};
  void removeNum(int num) {p_currentNum -= num;};
  double getProduceSpeed() const {return p_produceSpeed;};
  
  string getName() const {return p_goodsData->getName();};
  int getPrice() const {return p_goodsData->getPrice();};
};

class InvestBenefitsData
{
private:
  int p_cityLevel;  // key
  string p_affectedGoodsId;
  int p_addMaximum;
  float p_addProduceSpeed;
  int p_addLevel;
public:
  InvestBenefitsData(const nlohmann::json &investBenefitsJson);
  int getCityLevel() const {return p_cityLevel;};
};

class CityData
{
private:
  string p_id;
  string p_cityId;
  string p_cityName;
  string p_cityIconPath;
  pair<double, double> p_position;
  vector<const RouteData *> p_routes;
  unordered_map<GuildData *, int> p_cityControls;
  int p_level;
  int p_businessValue;
  vector<CityGoodsData *> p_goodsList;
  unordered_map<string, CityGoodsData *> p_goodsMap;
  unordered_map<int, InvestBenefitsData *> p_investMap;
public:
  CityData(const string &id);
  ~CityData();
  string getId() const {return p_id;};
  string getIcon() const {return p_cityIconPath;};
  string getName() const {return p_cityName;};
  pair<double, double> getPosition() const {return p_position;};
  vector<CityGoodsData *> getGoodsList() const {return p_goodsList;};
  unordered_map<GuildData *, int> getGuildControls() const {return p_cityControls;};
  void setId(const string &id) {p_id = id;};
  void setPosition(const pair<double, double> &position);
  void setLevel(int level);
  void addRoute(const RouteData *route) {p_routes.push_back(route);};
  void setCityControl(GuildData *guild, int value) {p_cityControls[guild] = value;};
  static CityData* loadCityDataWithOverrideJson(const nlohmann::json &cityJson);
  cocos2d::Color3B getControledCollor() const;
  GuildData* getControledByGuild() const;
  bool isBelongToGuild(GuildData* guildData);
  bool isMyCity() const;
};

#endif /* CityData_hpp */
