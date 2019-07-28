//
//  GoodsData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GoodsData.hpp"

#include "JSONContent.hpp"
#include "JsonUtils.hpp"

GoodsData::GoodsData(const string &id)
{
  auto path = "res/Data/Goods/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_id = JsonUtils::getStringFromJson(jsonContent, "id");
  p_name = JsonUtils::getStringFromJson(jsonContent, "name");
  p_price = JsonUtils::getIntFromJson(jsonContent, "price");
}
