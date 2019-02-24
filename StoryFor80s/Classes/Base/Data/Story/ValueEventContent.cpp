//
//  ValueEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "ValueEventContent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"

ValueEventContent::ValueEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_values = jsonContent.at("values");
}

void ValueEventContent::runEvent(BaseScene *baseScene, StoryEventCallback callback)
{
  for (auto iter = p_values.begin(); iter != p_values.end(); ++iter) {
    auto key = iter.key();
    auto value = Utils::getStringFromJson(p_values, key);
    DataManager::getShareInstance()->setValue(key, value);
  }
  callback();
}
