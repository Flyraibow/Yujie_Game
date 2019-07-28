//
//  GuildData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GuildData.hpp"
#include "JsonUtils.hpp"
#include "JSONContent.hpp"

GuildData::GuildData(const string &id)
{
  auto path = "res/Data/Guild/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_guildId = JsonUtils::getStringFromJson(jsonContent, "id");
  p_guildName = JsonUtils::getIntFromJson(jsonContent, "name");
}

GuildData* GuildData::loadGuildDataWithOverrideJson(const nlohmann::json &guildJson)
{
  auto guildId = JsonUtils::getStringFromJson(guildJson, "guild_id");
  auto guildData = new GuildData(guildId);
  guildData->setId(JsonUtils::getStringFromJson(guildJson, "id", guildId));
  return guildData;
}
