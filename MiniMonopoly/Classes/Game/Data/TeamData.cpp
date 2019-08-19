//
//  TeamData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "TeamData.hpp"
#include "GuildData.hpp"
#include "CityData.hpp"

TeamGoodsData::TeamGoodsData(CityGoodsData* cityGoodData, int number)
{
  p_num = number;
  p_level = cityGoodData->getLevel();
  p_buyPrice = cityGoodData->getPrice();
  p_goodsData = cityGoodData->getGoodsData();
  p_fromCity = cityGoodData->getCity();
}

string TeamGoodsData::getName() const
 {
   return p_goodsData->getName();
 }

int TeamGoodsData::getSellPrice(const CityData* cityData) const
{
  // need add the calculation of the city data;
  return p_buyPrice * 1.5;
}

TeamData::TeamData(GuildData* guildData)
{
  p_guildData = guildData;
  p_currentCity = nullptr;
  p_maxCapacity = 10;
}

int TeamData::getCurrentLoads() const
{
  int load = 0;
  for (auto goods : p_goodsList) {
    load += goods->getNum();
  }
  return load;
}

TeamData* TeamData::createTeam(GuildData* guildData, CityData* cityData)
{
  auto price = getCreatTeamPrice(guildData);
  CCASSERT(guildData->getMoney() >= price, "Not enough money to create team!");
  auto teamData = new TeamData(guildData);
  guildData->addTeam(teamData);
  guildData->setMoney(guildData->getMoney() - price);
  teamData->setName("name" + to_string(guildData->getTeams().size()));
  teamData->setCurrCity(cityData);
  return teamData;
}

int TeamData::getCreatTeamPrice(GuildData* guildData)
{
  int hasTeams = (int)guildData->getTeams().size();
  int value = 500 * pow(2, hasTeams);
  if (value < 0) {
    value = INT_MAX;
  }
  return value;
}

void TeamData::sellGoodsInCity(const unordered_map<TeamGoodsData *, int> &sellGoodsDict, CityData* cityData)
{
  for (int i = (int)p_goodsList.size() - 1; i >= 0; --i) {
    auto goods = p_goodsList.at(i);
    if (sellGoodsDict.count(goods) ) {
      auto number = sellGoodsDict.at(goods);
      CCASSERT(number <= goods->getNum(), "Something is wrong, there is no enough goods in the team");
      int num = goods->getNum() - number;
      goods->setNum(num);
      if (num <= 0) {
        p_goodsList.erase(p_goodsList.begin() + (i));
      }
    }
  }
}

void TeamData::buyGoodsInCity(const unordered_map<CityGoodsData *, int> &buyGoodsDict, CityData* cityData)
{
  for (auto buyGoodsPair : buyGoodsDict) {
    auto cityGoods = buyGoodsPair.first;
    auto number= buyGoodsPair.second;
    cityGoods->removeNum(number);
    auto teamGoods = new TeamGoodsData(cityGoods, number);
    p_goodsList.push_back(teamGoods);
  }
}
