//
//  GuildData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GuildData.hpp"
#include "JsonUtils.hpp"
#include "JSONContent.hpp"
#include "JsonUtils+cocos2d.hpp"

GuildData::GuildData(const string &id)
{
  auto path = "res/Data/Guild/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_guildId = JsonUtils::getStringFromJson(jsonContent, "id");
  p_guildName = JsonUtils::getStringFromJson(jsonContent, "name");
  auto color = JsonUtils::getColorFromJson(jsonContent, "color");
  p_color = Color3B(color);
}

GuildData* GuildData::loadGuildDataWithOverrideJson(const nlohmann::json &guildJson)
{
  auto guildId = JsonUtils::getStringFromJson(guildJson, "guild_id");
  auto guildData = new GuildData(guildId);
  guildData->setId(JsonUtils::getStringFromJson(guildJson, "id", guildId));
  guildData->setMoney(JsonUtils::getIntFromJson(guildJson, "money"));
  return guildData;
}
