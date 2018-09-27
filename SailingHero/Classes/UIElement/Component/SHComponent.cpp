//
//  SHComponent.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#include "SHComponent.hpp"
#include "JsonUtil.hpp"

std::string SHComponent::getId() const
{
  return p_id;
}

SHComponent::SHComponent(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  p_type = SHUtil::getStringFromJson(componentJson, "type");
  p_id = SHUtil::getStringFromJson(componentJson, "id");
  p_isAutoScale = SHUtil::getBoolFromJson(componentJson, "auto_scale");
  p_normalizePosition = SHUtil::getVec2FromJson(componentJson, "normalized_position");
  p_anchorPoint = SHUtil::getVec2FromJson(componentJson, "anchor_point", cocos2d::Vec2(0.5, 0.5));
  p_componentList = SHComponent::getComponentsFromJson(componentJson);
  if (componentJson.count("size")) {
    p_size = componentJson.at("size");
  }
}

Size SHComponent::getComponentSize(Node *parent) const
{
  float width = 0, height = 0;
  if (!p_size.empty() && p_size.is_object()) {
    if (p_size.count("width")) {
      width = p_size.at("width").get<double>();
    } else if (p_size.count("normalized_width")) {
      width = parent->getContentSize().width * p_size.at("normalized_width").get<float>();
    }
    if (p_size.count("height")) {
      height = p_size.at("height").get<double>();
    } else if (p_size.count("normalized_height")) {
      height = parent->getContentSize().height * p_size.at("normalized_height").get<float>();
    }
  }
  return Size(width, height);
}

void SHComponent::addNodeToParent(unordered_map<string, Node *> &dict, Node *child, Node *parent) const
{
  child->setAnchorPoint(p_anchorPoint);
  child->setNormalizedPosition(p_normalizePosition);
  child->setName(p_id);
  if (p_id.length() > 0) {
    if (dict.count(p_id)) {
      CCLOGWARN("duplicate id : %s", p_id.c_str());
    }
    dict[p_id] = child;
  }
  
  auto parentScale = parent ? parent->getScale() : 1;
  float f = 1.0 / parentScale;
  if (p_isAutoScale) {
    f *= Director::getInstance()->getContentScaleFactor();
  }
  child->setScale(f);
  
  for (int i = 0; i < p_componentList.size(); ++i) {
    p_componentList[i]->addComponentToParent(dict, child);
  }

  if (parent) {
    parent->addChild(child);
  }
}

#include "SHLabelComponent.hpp"
#include "SHButtonComponent.hpp"
#include "SHSpriteComponent.hpp"
#include "SHColorNodeComponent.hpp"
#include "SHEditBoxComponent.hpp"

SHComponent* SHComponent::getComponentFromJson(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  string type = componentJson.at("type");
  if (type == "label") {
    return new SHLabelComponent(componentJson);
  } else if (type == "button") {
    return new SHButtonComponent(componentJson);
  } else if (type == "sprite") {
    return new SHSpriteComponent(componentJson);
  } else if (type == "color_node") {
    return new SHColorNodeComponent(componentJson);
  }  else if (type == "edit_box") {
    return new SHEditBoxComponent(componentJson);
  } else {
    CCASSERT(false, ("unsupported type" + type).c_str());
  }
  return nullptr;
}

vector<SHComponent *> SHComponent::getComponentsFromJson(const nlohmann::json &componentJson)
{
  vector<SHComponent *> result;
  if (componentJson.count("components")) {
    auto componentJsonList = componentJson.at("components");
    for (int i = 0; i < componentJsonList.size(); ++i) {
      nlohmann::json componentJson = componentJsonList.at(i);
      result.push_back(SHComponent::getComponentFromJson(componentJson));
    }
  }
  return result;
}
