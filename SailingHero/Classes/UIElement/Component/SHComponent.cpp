//
//  SHComponent.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#include "SHComponent.hpp"

cocos2d::Vec2 getVec2FromJson(const nlohmann::json &json, const std::string &field, const cocos2d::Vec2 defaultValue = cocos2d::Vec2())
{
  if (json.count(field)) {
    auto vec = json.at(field);
    CCASSERT(vec.size() == 2, ("json is not Vec2 type : " + vec.dump()).c_str());
    return cocos2d::Vec2(vec.at(0).get<double>(), vec.at(1).get<double>());
  }
  return defaultValue;
}

std::string SHComponent::getId() const
{
  return p_id;
}

SHComponent::SHComponent(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  p_type = componentJson.at("type").get<std::string>();
  if (componentJson.count("id")) {
    p_id = componentJson.at("id").get<std::string>();
  }
  p_normalizePosition = getVec2FromJson(componentJson, "normalized_position");
  p_anchorPoint = getVec2FromJson(componentJson, "anchor_point", cocos2d::Vec2(0.5, 0.5));
}

#include "SHLabelComponent.hpp"
#include "SHButtonComponent.hpp"

SHComponent* SHComponent::getComponentFromJson(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  string type = componentJson.at("type");
  if (type == "label") {
    return new SHLabelComponent(componentJson);
  } else if (type == "button") {
    return new SHButtonComponent(componentJson);
  } else {
    CCASSERT(false, ("unsupported type" + type).c_str());
  }
  return nullptr;
}

vector<SHComponent *> SHComponent::getComponentsFromJson(const nlohmann::json &componentJsonList)
{
  vector<SHComponent *> result;
  for (int i = 0; i < componentJsonList.size(); ++i) {
    nlohmann::json componentJson = componentJsonList.at(i);
    result.push_back(SHComponent::getComponentFromJson(componentJson));
  }
  return result;
}
