//
//  SHLabelComponent.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#include "SHLabelComponent.hpp"
#include "LocalizationHelper.hpp"

USING_NS_CC;

SHLabelComponent::SHLabelComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  if (componentJson.count("text_size")) {
    p_textSize = componentJson.at("text_size").get<float>();
  }
  if (componentJson.count("text")) {
    p_text = componentJson.at("text").get<std::string>();
  }
}

Node *SHLabelComponent::generateComponent()
{
  auto text = p_text.size() > 0 ? LocalizationHelper::getLocalization(p_text) : "";
  auto label = Label::createWithSystemFont(text, "Helvetica", p_textSize);
  label->setName(p_id);
  label->setAnchorPoint(p_anchorPoint);
  label->setNormalizedPosition(p_normalizePosition);
  return label;
}
