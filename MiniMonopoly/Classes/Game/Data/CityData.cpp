//
//  CityData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "CityData.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"

CityData::CityData(const string &id)
{
  auto path = "res/Data/City/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
}

void CityData::setPosition(const pair<double, double> &position)
{
  p_position = position;
}

void CityData::setLevel(int level)
{
  p_level = level;
  // upgrade verything to latest level;
}

CityData* CityData::loadCityDataWithOverrideJson(const nlohmann::json &cityJson)
{
  auto cityId = JsonUtils::getStringFromJson(cityJson, "city_id");
  auto cityData = new CityData(cityId);
  auto position = JsonUtils::getPositionPairFromJson(cityJson, "position");
  cityData->setId(JsonUtils::getStringFromJson(cityJson, "id", cityId));
  cityData->setPosition(position);
  cityData->setLevel(JsonUtils::getIntFromJson(cityJson, "city_level"));
  return cityData;
}
