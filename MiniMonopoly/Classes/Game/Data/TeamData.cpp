//
//  TeamData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "TeamData.hpp"
#include "GuildData.hpp"

TeamData::TeamData(GuildData* guildData)
{
  p_guildData = guildData;
  p_currentCity = nullptr;
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
