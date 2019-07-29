//
//  CityData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "CityData.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"
#include "GoodsData.hpp"

CityGoodsData::CityGoodsData(const nlohmann::json &cityGoodsJson)
{
  auto goodsId = JsonUtils::getStringFromJson(cityGoodsJson, "goods_id");
  p_goodsData = new GoodsData(goodsId);
  p_level = JsonUtils::getIntFromJson(cityGoodsJson, "level");
  p_maxNum = JsonUtils::getIntFromJson(cityGoodsJson, "maximum");
  p_produceSpeed = JsonUtils::getDoubleFromJson(cityGoodsJson, "produce_speed");
}

CityGoodsData::~CityGoodsData()
{
  delete p_goodsData;
  p_goodsData = nullptr;
}

InvestBenefitsData::InvestBenefitsData(const nlohmann::json &investBenefitsJson)
{
  p_cityLevel = JsonUtils::getIntFromJson(investBenefitsJson, "city_level");
  p_affectedGoodsId = JsonUtils::getStringFromJson(investBenefitsJson, "goods_id");
  p_addMaximum = JsonUtils::getIntFromJson(investBenefitsJson, "add_maximum");
  p_addProduceSpeed = JsonUtils::getDoubleFromJson(investBenefitsJson, "add_produce_speed");
  p_addLevel = JsonUtils::getIntFromJson(investBenefitsJson, "add_level");
}

CityData::CityData(const string &id)
{
  auto path = "res/Data/City/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_cityId = JsonUtils::getStringFromJson(jsonContent, "id");
  p_level = JsonUtils::getIntFromJson(jsonContent, "cit_level");
  p_businessValue = JsonUtils::getIntFromJson(jsonContent, "business_value");
  p_cityIconPath = JsonUtils::getStringFromJson(jsonContent, "city_icon");
  
  auto goodJsonList = JsonUtils::getJsonListFromJson(jsonContent, "goods");
  for (auto cityGoodsJson : goodJsonList) {
    auto cityGoodData = new CityGoodsData(cityGoodsJson);
    p_goodsList.push_back(cityGoodData);
    p_goodsMap[cityGoodData->getId()] = cityGoodData;
  }
  
  auto investBenefitsJsonList = JsonUtils::getJsonListFromJson(jsonContent, "invest_benefits");
  for (auto investBenefitsJson : investBenefitsJsonList) {
    auto investBenefitsData = new InvestBenefitsData(investBenefitsJson);
    p_investMap[investBenefitsData->getCityLevel()] = investBenefitsData;
  }
}

CityData::~CityData()
{
  for (auto goods : p_goodsList) {
    delete goods;
  }
  p_goodsList.clear();
  p_goodsMap.clear();
  for (auto invest : p_investMap) {
    delete invest.second;
  }
  p_investMap.clear();
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
