//
//  BaseComponent.cpp
//
//  Created by Yujie Liu on 9/22/18.
//

#include "BaseComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "Utils.hpp"

std::string BaseComponent::getId() const
{
  return p_id;
}

BaseComponent::BaseComponent(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  p_associateData = nullptr;
  p_type = Utils::getStringFromJson(componentJson, "type");
  p_id = Utils::getStringFromJson(componentJson, "id");
  p_isAutoScale = Utils::getBoolFromJson(componentJson, "auto_scale");
  p_isParentScale = Utils::getBoolFromJson(componentJson, "parent_scale");
  p_shareData = Utils::getBoolFromJson(componentJson, "share_data");
  p_normalizePosition = Utils::getVec2FromJson(componentJson, "normalized_position");
  p_normalizePositionOffset = Utils::getVec2FromJson(componentJson, "normalized_position_offset");
  p_position = Utils::getVec2FromJson(componentJson, "position");
  p_positionOffset = Utils::getVec2FromJson(componentJson, "position_offset");
  p_anchorPoint = Utils::getVec2FromJson(componentJson, "anchor_point", cocos2d::Vec2(0.5, 0.5));
  p_componentList = BaseComponent::getComponentsFromJson(componentJson);
  p_shouldHideCondition = Utils::getStringFromJson(componentJson, "hide_condition");
  if (componentJson.count("size")) {
    p_size = componentJson.at("size");
  }
  p_scale = Utils::getFloatFromJson(componentJson, "scale", 1.0);
  p_isFullScreen = Utils::getBoolFromJson(componentJson, "full_screen");
  p_node = nullptr;
}

Size BaseComponent::getComponentSize(Node *parent) const
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

void BaseComponent::addNodeToParent(ComponentDict &dict, Node *child, Node *parent)
{
  CCLOG("adding panel id : %s", p_id.c_str());
  child->setAnchorPoint(p_anchorPoint);
  if (p_normalizePosition != Vec2::ZERO || p_normalizePositionOffset != Vec2::ZERO) {
    auto np = p_normalizePosition;
    if (p_normalizePositionOffset != Vec2::ZERO) {
      np = Vec2(p_normalizePosition.x + p_normalizePositionOffset.x * p_index, p_normalizePosition.y + p_normalizePositionOffset.y * p_index);
    }
    child->setNormalizedPosition(np);
  } else if (p_position != Vec2::ZERO || p_positionOffset != Vec2::ZERO) {
    auto p = p_position;
    if (p_positionOffset != Vec2::ZERO) {
      p = Vec2(p_position.x + p_positionOffset.x * p_index, p_position.y + p_positionOffset.y * p_index);
    }
    child->setPosition(p);
  }
  child->setName(p_id);
  if (p_id.length() > 0) {
    if (dict.count(p_id)) {
      CCLOGWARN("duplicate id : %s", p_id.c_str());
    }
    dict[p_id] = this;
  }
  
  if (p_isFullScreen) {
    auto scaleX = parent->getContentSize().width / child->getContentSize().width;
    auto scaleY = parent->getContentSize().height / child->getContentSize().height;
    child->setScale(scaleX, scaleY);
  } else {
    auto parentScale = parent ? parent->getScaleX() : 1;
    float f = 1.0;
    if (!p_isParentScale) {
      f /= parentScale;
      if (p_isAutoScale) {
        f *= Director::getInstance()->getContentScaleFactor();
      }
    }
    child->setScale(f * p_scale);
  }
  
  for (int i = 0; i < p_componentList.size(); ++i) {
    p_componentList[i]->addComponentToParent(dict, child);
  }

  if (parent) {
    parent->addChild(child);
  }
  p_node = child;
}

Vec2 BaseComponent::getVec2FromStringVec2(const vector<string> &list) const
{
  if (list.size() == 2) {
    auto posX = atof(decipherValue(list.at(0)).c_str());
    auto posY = atof(decipherValue(list.at(1)).c_str());
    return Vec2(posX, posY);
  }
  return Vec2();
}

string BaseComponent::decipherValue(const string &value) const
{
  auto arr = Utils::split(value, '.');
  if (arr.size() > 1 && arr.at(0) == "associate") {
    return p_associateData->getFieldValue(arr.at(1));
  }
  return DataManager::getShareInstance()->decipherString(value);
}

#include "LabelComponent.hpp"
#include "ButtonComponent.hpp"
#include "SpriteComponent.hpp"
#include "ColorNodeComponent.hpp"
#include "EditBoxComponent.hpp"
#include "PanelComponent.hpp"
#include "ListComponent.hpp"
#include "ScrollViewComponent.hpp"

BaseComponent* BaseComponent::getComponentFromJson(const nlohmann::json &componentJson)
{
  CCASSERT(componentJson.count("type"), ("Component type is required. json : " + componentJson.dump()).c_str());
  string type = componentJson.at("type");
  if (type == "label") {
    return new LabelComponent(componentJson);
  } else if (type == "button") {
    return new ButtonComponent(componentJson);
  } else if (type == "sprite") {
    return new SpriteComponent(componentJson);
  } else if (type == "color_node") {
    return new ColorNodeComponent(componentJson);
  } else if (type == "edit_box") {
    return new EditBoxComponent(componentJson);
  } else if (type == "panel") {
    return new PanelComponent(componentJson);
  } else if (type == "scrollView") {
    return new ScrollViewComponent(componentJson);
  } else if (type == "componentList") {
    return new ListComponent(componentJson);
  } else {
    CCASSERT(false, ("unsupported type" + type).c_str());
  }
  return nullptr;
}

vector<BaseComponent *> BaseComponent::getComponentsFromJson(const nlohmann::json &componentJson)
{
  vector<BaseComponent *> result;
  if (componentJson.count("components")) {
    auto componentJsonList = componentJson.at("components");
    for (int i = 0; i < componentJsonList.size(); ++i) {
      nlohmann::json componentJson = componentJsonList.at(i);
      result.push_back(BaseComponent::getComponentFromJson(componentJson));
    }
  }
  return result;
}

void BaseComponent::setIndex(int index)
{
  p_index = index;
}

void BaseComponent::copyAttributesFromJson(const nlohmann::json &componentJson)
{
  p_id = Utils::getStringFromJson(componentJson, "id");
  
  p_isAutoScale = Utils::getBoolFromJson(componentJson, "auto_scale", p_isAutoScale);
  p_isParentScale = Utils::getBoolFromJson(componentJson, "parent_scale", p_isParentScale);
  p_normalizePositionOffset = Utils::getVec2FromJson(componentJson, "normalized_position_offset", p_normalizePositionOffset);
  p_normalizePosition = Utils::getVec2FromJson(componentJson, "normalized_position", p_normalizePosition);
  p_positionOffset = Utils::getVec2FromJson(componentJson, "position_offset", p_positionOffset);
  p_position = Utils::getVec2FromJson(componentJson, "position", p_position);
  p_anchorPoint = Utils::getVec2FromJson(componentJson, "anchor_point", p_anchorPoint);
  if (componentJson.count("size")) {
    p_size = componentJson.at("size");
  }
  p_scale = Utils::getFloatFromJson(componentJson, "scale", p_scale);
  p_isFullScreen = Utils::getBoolFromJson(componentJson, "full_screen", p_isFullScreen);
  p_shouldHideCondition = Utils::getStringFromJson(componentJson, "hide_condition", p_shouldHideCondition);
}

void BaseComponent::refresh()
{
  if (p_shouldHideCondition.length() > 0) {
    p_node->setVisible(!DataManager::getShareInstance()->checkCondition(p_shouldHideCondition));
  }
}

void BaseComponent::setAssociateData(BaseData *baseData) {
  p_associateData = baseData;
  if (p_shareData) {
    for (int i = 0; i < p_componentList.size(); ++i) {
      p_componentList.at(i)->setAssociateData(baseData);
    }
  }
}
