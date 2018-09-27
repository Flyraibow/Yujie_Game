//
//  SHLabelComponent.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#include "SHLabelComponent.hpp"
#include "LocalizationHelper.hpp"
#include "JsonUtil.hpp"

USING_NS_CC;

SHLabelComponent::SHLabelComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_textSize = SHUtil::getFloatFromJson(componentJson, "text_size");
  p_text = SHUtil::getStringFromJson(componentJson, "text");
  p_normalizedDimension = SHUtil::getVec2FromJson(componentJson, "normalized_dimensions");
}

Node* SHLabelComponent::addComponentToParent(unordered_map<string, Node *> &dict, Node *parent) const
{
  auto text = p_text.size() > 0 ? LocalizationHelper::getLocalization(p_text) : "";
  auto label = Label::createWithSystemFont(text, "Helvetica", p_textSize);
  
  if (parent) {
    if (!p_normalizedDimension.isZero()) {
      label->setDimensions(parent->getContentSize().width * p_normalizedDimension.x,
                           parent->getContentSize().height * p_normalizedDimension.y);
    }
  }
  addNodeToParent(dict, label, parent);
  return label;
}
