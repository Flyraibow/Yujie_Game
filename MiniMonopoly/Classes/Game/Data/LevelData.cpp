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
  auto guildsList = JsonUtils::getJsonListFromJson(jsonContent, "guilds");
  for (auto jsonGuild : guildsList) {
    auto guildData = GuildData::loadGuildDataWithOverrideJson(jsonGuild);
    p_guildData.push_back(guildData);
    
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
}


CityData* LevelData::getCityData(const string &id)
{
  auto city = p_citiesMap[id];
  CCASSERT(city != nullptr, ("Route's city is not defined" + id).c_str());
  return city;
}
