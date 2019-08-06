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
  p_price = cityGoodData->getPrice();
  p_goodsData = cityGoodData->getGoodsData();
  p_fromCity = cityGoodData->getCity();
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
