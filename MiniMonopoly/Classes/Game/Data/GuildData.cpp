//
//  GuildData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GuildData.hpp"
#include "JsonUtils.hpp"

GuildData::GuildData(const string &fileName)
{
  
}

GuildData* GuildData::loadGuildDataWithOverrideJson(const nlohmann::json &guildJson)
{
  auto guildId = JsonUtils::getStringFromJson(guildJson, "guild_id");
  auto guildData = new GuildData(guildId);
  guildData->setId(JsonUtils::getStringFromJson(guildJson, "id", guildId));
  return guildData;
}
