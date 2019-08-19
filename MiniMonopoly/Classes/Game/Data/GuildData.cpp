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
#include "ObserverManager.h"

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
  guildData->setIsPlayer(JsonUtils::getBoolFromJson(guildJson, "is_player"));
  return guildData;
}


void GuildData::setMoney(int money) {
  p_money = money;
  for (auto callbackPair : p_moneyChangeCallbacks) {
    auto callback = callbackPair.second;
    callback();
  }
}


void GuildData::addMoneyChangeCallback(const string& key, mmGuildMoneyChangeCallback callback)
{
  if (p_moneyChangeCallbacks.count(key) == 0) {
    p_moneyChangeCallbacks[key] = callback;
  }
}

void GuildData::removeMoneyChangeCallback(const string& key)
{
  p_moneyChangeCallbacks.erase(key);
}
