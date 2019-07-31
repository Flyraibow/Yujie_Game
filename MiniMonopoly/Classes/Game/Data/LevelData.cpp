//
//  LevelData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "LevelData.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"

LevelData::LevelData(const string &fileName)
{
  auto path = "res/Data/Level/" + fileName + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_id = JsonUtils::getStringFromJson(jsonContent, "id", fileName);
  p_name = JsonUtils::getStringFromJson(jsonContent, "name");
  p_mapPath = JsonUtils::getStringFromJson(jsonContent, "map");
  p_iconPath = JsonUtils::getStringFromJson(jsonContent, "icon");
  auto cityJsonList = JsonUtils::getJsonListFromJson(jsonContent, "cities");
  for (auto jsonCity : cityJsonList) {
    auto cityData = CityData::loadCityDataWithOverrideJson(jsonCity);
    p_cities.push_back(cityData);
    p_citiesMap[cityData->getId()] = cityData;
  }
  auto routesList = JsonUtils::getJsonListFromJson(jsonContent, "routes");
  for (auto routeJson : routesList) {
    auto cities = JsonUtils::getStringListFromJson(routeJson, "cities");
    auto distance = JsonUtils::getFloatFromJson(routeJson, "distance");
    if (cities.size() > 0) {
      auto firstCity = getCityData(cities.at(0));
      for (int i = 1; i < cities.size(); ++i) {
        auto secondCity = getCityData(cities.at(i));
        auto route1 = new RouteData(secondCity, distance);
        firstCity->addRoute(route1);
        auto route2 = new RouteData(firstCity, distance);
        secondCity->addRoute(route2);
      }
    }
  }
  p_myGuild = nullptr;
  auto guildsList = JsonUtils::getJsonListFromJson(jsonContent, "guilds");
  for (auto jsonGuild : guildsList) {
    auto guildData = GuildData::loadGuildDataWithOverrideJson(jsonGuild);
    p_guildList.push_back(guildData);
    if (guildData->isPlayer()) {
      p_myGuild = guildData;
    }
    
    auto cityConrolsJson = JsonUtils::getChildJsonFromJson(jsonGuild, "city_controls");
    auto keys = JsonUtils::getKeysFromJson(cityConrolsJson);
    for (auto cityId : keys) {
      auto city = getCityData(cityId);
      auto cityControlValue = JsonUtils::getIntFromJson(cityConrolsJson, cityId);
      if (cityControlValue > 0) {
        guildData->setCityControl(city, cityControlValue);
        city->setCityControl(guildData, cityControlValue);
      }
    }
  }
  CCASSERT(p_myGuild != nullptr, "My guild is not set");
}

LevelData::~LevelData()
{
  for (auto city : p_cities) {
    delete city;
  }
  p_cities.clear();
  p_citiesMap.clear();
  for (auto guild : p_guildList) {
    delete guild;
  }
  p_guildList.clear();
}

CityData* LevelData::getCityData(const string &id) const
{
  CCASSERT(p_citiesMap.count(id), ("Route's city is not defined" + id).c_str());
  auto city = p_citiesMap.at(id);
  return city;
}

