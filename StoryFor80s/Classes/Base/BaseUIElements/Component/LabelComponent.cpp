//
//  LabelComponent.cpp
//
//  Created by Yujie Liu on 9/22/18.
//

#include "LabelComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "BaseLabel.hpp"

USING_NS_CC;

LabelComponent::LabelComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_textSize = Utils::getFloatFromJson(componentJson, "text_size");
  p_text = Utils::getStringFromJson(componentJson, "text");
  p_normalizedDimension = Utils::getVec2FromJson(componentJson, "normalized_dimensions");
  p_speed = Utils::getIntFromJson(componentJson, "speed");
}

Node* LabelComponent::addComponentToParent(ComponentDict &dict, Node *parent)
{
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text, p_associateData) : "";
  BaseLabel *label = BaseLabel::createWithSystemFont(text, "Helvetica", p_textSize, p_speed);
  
  if (parent) {
    if (!p_normalizedDimension.isZero()) {
      label->setDimensions(parent->getContentSize().width * p_normalizedDimension.x,
                           parent->getContentSize().height * p_normalizedDimension.y);
    }
  }
  addNodeToParent(dict, label, parent);
  return label;
}

void LabelComponent::refresh()
{
  BaseComponent::refresh();
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text, p_associateData) : "";
  auto label = dynamic_cast<BaseLabel *>(p_node);
  label->setString(text);
}
