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
  int p_level;
  int p_maxNum;
  double p_produceSpeed;
public:
  CityGoodsData(const nlohmann::json &cityGoodsJson);
  ~CityGoodsData();
  string getId() const {return p_goodsData->getId();};
  int getLevel() const {return p_level;};
  int getMaxNum() const {return p_maxNum;};
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
  void setId(const string &id) {p_id = id;};
  void setPosition(const pair<double, double> &position);
  void setLevel(int level);
  void addRoute(const RouteData *route) {p_routes.push_back(route);};
  void setCityControl(GuildData *guild, int value) {p_cityControls[guild] = value;};
  static CityData* loadCityDataWithOverrideJson(const nlohmann::json &cityJson);
};

#endif /* CityData_hpp */
