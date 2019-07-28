//
//  SimpleLevelData.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/27/19.
//

#include "SimpleLevelData.hpp"
#include "JSONContent.hpp"
#include "JsonUtils.hpp"


SimpleLevelData::SimpleLevelData(const string &id)
{
  auto path = LEVEL_FILE_FOLDER + "/" + id + ".json";
  auto jsonContent = JSONContent::loadJsonFromPath(path);
  p_id = JsonUtils::getStringFromJson(jsonContent, "id", id);
  p_name = JsonUtils::getStringFromJson(jsonContent, "name");
  p_iconPath = JsonUtils::getStringFromJson(jsonContent, "icon");
}

SimpleLevelData::SimpleLevelData(const nlohmann::json &jsonContent)
{
  p_id = JsonUtils::getStringFromJson(jsonContent, "id");
  p_name = JsonUtils::getStringFromJson(jsonContent, "name");
  p_iconPath = JsonUtils::getStringFromJson(jsonContent, "icon");
}
